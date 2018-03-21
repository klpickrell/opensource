#ifndef INCLUDED_MATRIX__H
#define INCLUDED_MATRIX__H

// file: matrix.h
// author:  Kris Pickrell (kp26069@txstate.edu)
// description:  Homework 3 - generate MxN threads to multiply matrices A and B
//      of dimensions MxC and DxN respectively, where each thread takes a row
//      column pair and stores the result for output
//      This file contains some useful data structures
// class: CS5306 - Fall 07

#include <assert.h>
#include <stdlib.h>

typedef struct _this_r {
    int* data;
    int col_count;
    struct _this_r* next;

    void (*init)( struct _this_r* );
    void (*cleanup)( struct _this_r* );
    void (*set_data)( struct _this_r*, int col_count, int* rowdata );
} IntegerRow;

typedef IntegerRow Row;
typedef Row Column;
typedef int RowDataType;

void __init_row( Row* r )
{
    r->data = 0;
    r->col_count = 0;
    r->next = 0;
}

void __cleanup_row( Row* r )
{
    if( r ) {
	if( r->data ) {
	    free( r->data );
	    r->data = 0;
	    r->col_count = 0;
	    r->next = 0;
	}
    }
}

void __set_data( Row* r, int col_count, int* data )
{
    r->cleanup( r );
    if( data ) {
	r->data = (int*) malloc( col_count * sizeof( RowDataType ) );
	memcpy( r->data, data, col_count*sizeof( RowDataType ) );
	r->col_count = col_count;
    }
}

Row* create_row()
{
    Row* row = (Row*) malloc( sizeof( Row ) );
    if( row ) {
	row->init = __init_row;
	row->cleanup = __cleanup_row;
	row->set_data = __set_data;

	row->init( row );
    }
    return row;
}

typedef struct _this_m {
    Row* firstrow;

    void (*init)( struct _this_m* );
    void (*cleanup)( struct _this_m* );
    int (*row_count)( struct _this_m* );
    int (*col_count)( struct _this_m* );
    void (*add_row)( struct _this_m*, Row* row );
    Row* (*get_row)( struct _this_m*, int idx );
    Column* (*extract_column)( struct _this_m*, int idx );

} Matrix;

void __init_matrix( Matrix* m )
{
    m->firstrow = 0;
}

void __cleanup_matrix( Matrix* m )
{
    if( m ) {
	if( m->firstrow ) {
	    Row* row = m->firstrow;
	    while( row ) {
		Row* nextone = row->next;
		row->cleanup( row );
		row = nextone;
	    }

	    free( m->firstrow );
	}
    }
}

int __row_count( Matrix* m )
{
    int count = 0;
    Row* row = m->firstrow;
    while( row ) {
	count++;
	row = row->next;
    }

    return count;
}

int __col_count( Matrix* m )
{
    int count = 0;
    if( m ) {
	if( m->firstrow ) {
	    count = m->firstrow->col_count;
	}
    }

    return count;
}

void __add_row( Matrix* m, Row* row ) 
{
    if( !row ) {
	return;
    }

    if( m ) {
	if( !m->firstrow ) {
	    m->firstrow = row;
	} else {
	    Row* end = m->firstrow;
	    assert( end->col_count == row->col_count );
	    while( end->next ) {
		end = end->next;
		assert( end->col_count == row->col_count );
	    }
	    
	    end->next = row;
	}
    }
}

Row* __get_row( Matrix* m, int idx )
{
    Row* row = 0;
    if( idx >= 0 ) {
	if( m ) {
	    row = m->firstrow;
	    int i;
	    for( i = 0;
		 i < idx && row;
		 i++ ) {
		row = row->next;
	    }
	}
    }
    
    return row;
}

Column* __extract_column( Matrix* m, int idx )
{
    Column* column = 0;
    if( idx >= 0 ) {
	if( m ) {
	    int cols = m->col_count( m );
	    if( cols ) {
		int* colvec = (int*)calloc( cols*sizeof(int),1 );
		Row* row = m->firstrow;
		int iter = 0;
		while( row ) {
		    colvec[ iter ] = row->data[ idx ];
		    row = row->next;
		}

		column = create_row();
		column->col_count = cols;
		column->data = colvec;
	    }
	}
    }

    return column;
}

Matrix* create_matrix()
{
    Matrix* m = (Matrix*) malloc( sizeof( Matrix ) );
    if( m ) {
	m->firstrow = 0;
	m->init = __init_matrix;
	m->cleanup = __cleanup_matrix;
	m->row_count = __row_count;
	m->col_count = __col_count;
	m->add_row = __add_row;
	m->get_row = __get_row;
	m->extract_column = __extract_column;
    }

    return m;
}

#endif
