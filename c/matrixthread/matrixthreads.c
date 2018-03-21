// file: matrixthreads.c
// author:  Kris Pickrell (kp26069@txstate.edu)
// description:  Homework 3 - generate MxN threads to multiply matrices A and B
//      of dimensions MxC and DxN respectively, where each thread takes a row
//      column pair and stores the result for output

// class: CS5306 - Fall 07

#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "matrix.h"

// result
int** results_matrix = 0;

// shield access by mutexes
pthread_mutex_t results_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mem_mutex = PTHREAD_MUTEX_INITIALIZER;

void submit_results( int rownum, int columnnum, int sum )
{
    pthread_mutex_lock( &results_mutex );
    results_matrix[rownum][columnnum] = sum;
    pthread_mutex_unlock( &results_mutex );
}


// not entirely sure if stdlib memory management is threadsafe on this
// platform, protect access with mutexes

void* rmalloc( int size )
{
    pthread_mutex_lock( &mem_mutex );
    void* arg = malloc( size );
    pthread_mutex_unlock( &mem_mutex );
    return arg;
}

void* rcalloc( int size, int num )
{
    pthread_mutex_lock( &mem_mutex );
    void* arg = calloc( size, num );
    pthread_mutex_unlock( &mem_mutex );
    return arg;
}

void rfree( void* mem )
{
    pthread_mutex_lock( &mem_mutex );
    free( mem );
    pthread_mutex_unlock( &mem_mutex );
}

// an argument for each thread

typedef struct {
    int row;
    int column;
    int** matrix1;
    int** matrix2;
    int entry_count;
} ComputeMatrixProductArgs;


// print out a matrix

void print_matrix( int** matrix, int m, int n )
{
    int i,j;
    for( i = 0; i < m; i++ ) {
	printf( "[" );
	for( j = 0; j < n; j++ ) {
	    printf( " %d", matrix[i][j] );
	}
	printf( " ]\n" );
    }
}


// this is the thread routine, it computes the product of the row
// and column that it is given and submits the result to the result matrix

void* compute_matrix_product( void* arg )
{
    ComputeMatrixProductArgs* args = (ComputeMatrixProductArgs*)arg;
    int sum = 0;
    int i;

    for( i = 0; i < args->entry_count; i++ ) {
	pthread_mutex_lock( &sum_mutex );
	sum += args->matrix1[args->row][i]*args->matrix2[i][args->column];
	pthread_mutex_unlock( &sum_mutex );
    }

    submit_results( args->row, args->column, sum );
    rfree( args );

    return 0;
}


int main( int argc, char** argv )
{
    char input_buf[ 1024 ];
    int input_ints[ 256 ];
    int input_column_count = 0;
    int done = 0;
    Matrix* matrix1 = create_matrix();
    Matrix* matrix2 = create_matrix();

    int matrix1complete = 0;
    int matrix2complete = 0;

    typedef enum { SCAN_START, SCAN_ROW } state;
    const char* delims = ", \t\n";
    state current_state = SCAN_START;

    // scan stdin for lines that look like a matrix.  The format is described in 
    // the included file 'input.txt'

    while( !done ) {

	switch( current_state ) {
	case SCAN_START:
	    {
		input_column_count = 0;
		if( !fgets( input_buf, sizeof( input_buf ), stdin ) ) {
		    fprintf( stderr, "unexpected end of input\n" );
		    matrix1->cleanup( matrix1 );
		    matrix2->cleanup( matrix2 );
		    free( matrix1 );
		    free( matrix2 );
		    return 0;
		}
		
		char* token = strtok( input_buf, delims );
		if( !token || strcasecmp( token, "#" ) == 0 ) {
		    continue;
		}

		if( strcasecmp( token, "[" ) == 0 ) {

		    token = strtok( 0, delims );
		    if( strcasecmp( token, "[" ) == 0 ) {
			token = strtok( 0, delims );
			while( token ) {
			    if( strcasecmp( token, "]" ) == 0 ) {
				current_state = SCAN_ROW;
				break;
			    }

			    input_ints[ input_column_count ] = atol( token );
			    input_column_count++;

			    token = strtok( 0, delims );
			}

			if( current_state != SCAN_ROW ) {
			    fprintf( stderr, "missing ] in input\n" );
			    matrix1->cleanup( matrix1 );
			    matrix2->cleanup( matrix2 );
			    free( matrix1 );
			    free( matrix2 );
			    return 0;
			}

			if( input_column_count ) {
			    Row* row = create_row();
			    row->set_data( row, input_column_count, input_ints );
			    if( matrix1complete ) {
				matrix2->add_row( matrix2, row );
			    } else {
				matrix1->add_row( matrix1, row );
			    }
			}

		    } else {
			fprintf( stderr, "input error: expected [\n" );
		    }
		} else {
		    fprintf( stderr, "input error: expected [\n" );
		}
	    }
	    break;
	case SCAN_ROW:
	    {
		if( !fgets( input_buf, sizeof( input_buf ), stdin ) ) {
		    fprintf( stderr, "unexpected end of input\n" );
		    matrix1->cleanup( matrix1 );
		    matrix2->cleanup( matrix2 );
		    free( matrix1 );
		    free( matrix2 );
		    return 0;
		}

		int local_column_count = 0;
		char* token = strtok( input_buf, delims );

		if( !token || strcasecmp( token, "#" ) == 0 ) {
		    continue;
		}

		if( strcasecmp( token, "[" ) == 0 ) {
		    token = strtok( 0, delims );
		    while( token ) {
			if( strcasecmp( token, "]" ) == 0 ) {
			    if( local_column_count != input_column_count ) {
				fprintf( stderr, "invalid column counts in subsequent rows in inputs\n" );
				matrix1->cleanup( matrix1 );
				matrix2->cleanup( matrix2 );
				free( matrix1 );
				free( matrix2 );
				return 0;
			    }

			    if( local_column_count ) {
				Row* row = create_row();
				row->set_data( row, local_column_count, input_ints );
				if( matrix1complete ) {
				    matrix2->add_row( matrix2, row );
				} else {
				    matrix1->add_row( matrix1, row );
				}
			    }

			    token = strtok( 0, delims );
			    if( token ) {
				if( strcasecmp( token, "]" ) == 0 ) {
				    if( matrix1complete ) {
					done = 1;
				    } else {
					current_state = SCAN_START;
					matrix1complete = 1;
				    }
				} else {
				    fprintf( stderr, "input error encountered, expected ] in input\n" );
				    matrix1->cleanup( matrix1 );
				    matrix2->cleanup( matrix2 );
				    free( matrix1 );
				    free( matrix2 );
				    return 0;
				}
			    }

			    break;
			}

			input_ints[ local_column_count ] = atol( token );
			local_column_count++;

			token = strtok( 0, delims );
		    }
		} else {
		    fprintf( stderr, "input error: expected [\n" );
		}

	    } break;
	}
    }

    // now that we have the input, construct some data structures that the 
    // thread routine can use

    int i, j;

    int array1rows = matrix1->row_count( matrix1 );
    int array1cols = matrix1->col_count( matrix1 );

    int array2rows = matrix2->row_count( matrix2 );
    int array2cols = matrix2->col_count( matrix2 );

    // sanity check

    if( array1cols != array2rows ) {
	fprintf( stderr, "ERROR: array 1 number of columns must equal array 2 number of rows\n" );
	matrix1->cleanup( matrix1 );
	matrix2->cleanup( matrix2 );
	free( matrix1 );
	free( matrix2 );
	return 0;
    }

    results_matrix = (int**) rcalloc( array1rows * sizeof(int*),1 );
    for( i = 0; i < array1rows; i++ ) {
	results_matrix[i] = (int*) rcalloc( array2cols * sizeof( int ), 1 );
    }


    int** array1 = (int**) rmalloc( array1rows*sizeof(int*) );
    for( i = 0; i < array1rows; i++ ) {
	array1[i] = (int*) rmalloc( array1cols*sizeof(int) );
	Row* row = matrix1->get_row( matrix1, i );
	memcpy( array1[i], row->data, array1cols*sizeof(int) );
    }


    int** array2 = (int**) rmalloc( array2rows*sizeof(int*) );
    for( i = 0; i < array2rows; i++ ) {
	array2[i] = (int*) rmalloc( array2cols*sizeof(int) );
	Row* row = matrix2->get_row( matrix2, i );
	memcpy( array2[i], row->data, array2cols*sizeof(int) );
    }


    // done with input matrices
    matrix1->cleanup( matrix1 );
    free( matrix1 );

    matrix2->cleanup( matrix2 );
    free( matrix2 );

    printf( "array 1 is:\n" );
    print_matrix( array1, array1rows, array1cols );

    printf( "array 2 is:\n" );
    print_matrix( array2, array2rows, array2cols );

    // store thread_ids for calls to pthread_join

    pthread_t** thread_ids = (pthread_t**)rcalloc( array1rows * sizeof( pthread_t* ), 1 );
    for( i = 0; i < array1rows; i++ ) {
	thread_ids[i] = (pthread_t*)rcalloc( array2cols * sizeof( pthread_t ), 1 );
    }

    // launch the threads
    int success = 1;
    for( i = 0; i < array1rows; i++ ) {
	for( j = 0; j < array2cols; j++ ) {
	    // multiply m1[i] row and m2[j] column
	    ComputeMatrixProductArgs* args = (ComputeMatrixProductArgs*)rmalloc( sizeof( ComputeMatrixProductArgs ) );
	    args->row = i;
	    args->column = j;

	    args->matrix1 = (int**)array1;
	    args->matrix2 = (int**)array2;
	    args->entry_count = array1cols;

	    int ret = pthread_create( &thread_ids[i][j], 0, compute_matrix_product, (void*)args );
	    if( ret != 0 ) {
		success = 0;
		printf( "thread creation failure, errno=%s\n", strerror( errno ) );
		goto breakpoint;
	    }
	}
    }

    printf( "created threads to compute matrix product\n" );


breakpoint:
    // wait on whatever threads we managed to start
    for( i = 0; i < array1rows; i++ ) {
	for( j = 0; j < array2cols; j++ ) {
	    void* arg = 0;
	    int res = pthread_join( thread_ids[i][j], &arg ); // returns 0 on success
	    if( res ) {
		printf( "pthread_join failure: %s\n", strerror( errno ) );
		success = 0;
	    }

	    if( arg ) {
		printf( "thread %d returned %d\n", thread_ids[i][j], *(int*)arg );
		rfree( arg );
	    }
	}
    }

    // if we succeeded in launching all threads
    if( success ) {
	// print out matrix
	printf( "computed matrix product array1 * array2:\n" );
	print_matrix( results_matrix, array1rows, array2cols );
    }

    // cleanup our memory
    for( i = 0; i < array1rows; i++ ) {
    	rfree( thread_ids[ i ] );
    }

    rfree( thread_ids );

    for( i = 0; i < array1rows; i++ ) {
	rfree( array1[i] );
    }

    rfree( array1 );

    for( i = 0; i < array2rows; i++ ) {
	rfree( array2[i] );
    }

    rfree( array2 );
			
    for( i = 0; i < array1rows; i++ ) {
	rfree( results_matrix[i] );
    }

    rfree( results_matrix );

    return 0;
}
