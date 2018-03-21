#include <iostream>
#include <errno.h>
#include <string.h>

using namespace std;

int insert(int array[], int length, int value) 
{
  int instrcount = 1;
  int i = length - 1; instrcount++;

  while (i >= 0 and array[i] > value) { instrcount++; instrcount++;

    array[i + 1] = array[i]; instrcount++;
    i--; instrcount++;
  }

  array[i + 1] = value; instrcount++;
  return instrcount; 
}
 
int insertion_sort2(int array[], int length) 
{
  int instrcount = 1;
  int i = 1; instrcount++;

  while (i < length) { instrcount++;

  instrcount += insert(array, i, array[i]) + 1;
  i++; instrcount++;

  }

  instrcount++;
  return instrcount;
}

// Listing: insertion_sort
// Arguments: int array[] -- array to be sorted,
//            int length -- length of "array"
// Returns: number of lines executed
// Notes:  Iterates backwards from i-1 until
// it finds the proper slot, then it swaps it with value
// at location i

int insertion_sort( int array[], int length )
{
  // instrcount is ~ number of lines executed - should grow like n^2
  int instrcount = 1;
  for( int i = 1; i < length; i++) { 
                                           instrcount++; instrcount++;
    int temp = array[i];                   instrcount++;
    int j = i-1;

    while( j >= 0 && temp < array[j] ) {
                                           instrcount++; 
      array[j+1] = array[j];               instrcount++;
      j--;                                 instrcount++;
    }
    array[j+1] = temp;                     instrcount++; instrcount++;
  }

  return instrcount;
}

int insertion3_sort( int array[], int length )
{
  int instruction_count = 1;
  int i = 1; instruction_count++;
  while( i < length ) { instruction_count++;
    for( int j = 0; j < i; j++ ) { instruction_count++; instruction_count++;
      if( array[i] < array[j] ) { instruction_count++;
	int temp = array[i]; instruction_count++;
	array[i] = array[j]; instruction_count++;
	array[j] = temp; instruction_count++;
      }
    }

    i++; instruction_count++;
  }

  instruction_count++;
  return instruction_count;
}

bool test_insertion( int tcount )
{
  bool success = true;
  srand( time( 0 ) );
  FILE* fp = fopen( "./insertion.out", "wt" );

  if( !fp ) {
    cout << "failed to open output file insertion.out" << endl;
    return false;
  }

  int trials[] = { 8, 17, 31, 43, 51, 60, 72, 79, 92, 100 };
  int trialcount = sizeof( trials ) / sizeof( trials[0] );

  for( int i = 0; i < trialcount; i++ ) {

    int size = trials[i];
    int* array = new int[ size ];

    for( int j = 0; j < size; j++ ) {
      array[ j ] = (rand()/(float)RAND_MAX) * 1000;
    }

    cout << "trial #" << i+1 << " before: ";
    for( int j = 0; j < size; j++ ) {
      cout << array[ j ] << " ";
    }
    cout << endl;

    int count = insertion_sort( array, size );
    fprintf( fp, "%d\t%d\n", size, count );

    cout << "trial #" << i+1 << " after: ";
    for( int j = 0; j < size; j++ ) {
      cout << array[ j ] << " ";
    }
    cout << endl;
    
    if( size ) {
      int last = array[0];
      for( int j = 1; j < size; j++ ) {
	if( array[j] >= last ) {
	  last = array[j];
	} else {
	  cout << "sequence comparison failure on array: " << endl;
	  for( int p = 0; p < size; p++ )
	    cout << array[p] << " ";
	  cout << endl << "size=" << size << ", index=" << j << endl;
	  delete[] array;
	  success = false;
	  break;
	}
      }
    }


    delete[] array;
  }

  return success;
}

unsigned int merge2( int array[], int begin, int middle, int end )
{
    unsigned int instruction_count = 1;

    int left_size = middle - begin + 1; instruction_count++;
    int right_size = end - middle; instruction_count++;

    int* left = (int*)malloc( left_size * sizeof( int )); instruction_count++;
    int* right = (int*)malloc( right_size * sizeof( int )); instruction_count++;

    for( int i = 0; i < left_size; i++ ) { instruction_count++; instruction_count++;
	left[i] = array[ begin + i ]; instruction_count++;
    }

    for( int i = 0; i < right_size; i++ ) { instruction_count++; instruction_count++;
	right[i] = array[ middle + i + 1 ]; instruction_count++;
    }

    int i = 0; instruction_count++;
    int j = 0; instruction_count++;
    for( int k = begin; k <= end; k++ ) { instruction_count++; instruction_count++;

	if( i < left_size ) { instruction_count++;
	    if( j < right_size ) { instruction_count++;
		if( left[i] <= right[j] ) { instruction_count++;
		    array[k] = left[i]; instruction_count++;
		    i++; instruction_count++;
		} else {
		    array[k] = right[j]; instruction_count++;
		    j++; instruction_count++;
		}
	    } else {
		array[k] = left[i]; instruction_count++;
		i++; instruction_count++;
	    }
	} else {
	    array[k] = right[j]; instruction_count++;
	    j++; instruction_count++;
	}
    }

    free( left ); instruction_count++;
    free( right ); instruction_count++;
    return instruction_count;
}

unsigned int merge_sort2( int array[], int begin, int end )
{
    unsigned int instruction_count = 1;
    
    instruction_count++;
    if( begin < end ) {
	int middle = (begin+end)/2; instruction_count++;
	instruction_count += merge_sort2( array, begin, middle ); instruction_count++;
	instruction_count += merge_sort2( array, middle+1, end ); instruction_count++;
	merge2( array, begin, middle, end ); instruction_count++;
    }

    return instruction_count;
}

// Listing: merge_sort
// Arguments:  array to be sorted followed by beginning and ending indices
// Returns:  number of lines of code executed

int merge( int array[], int begin, int mid, int end )
{
  int instr_count = 1;

  int* sorted = new int[ end-begin + 1 ]; instr_count++;

  int left = begin; instr_count++;
  int right = mid+1; instr_count++;

  int cursor = 0; instr_count++;

  while( left <= mid && right <= end )
    {
      instr_count++;
      instr_count++;
      if( array[ left ] <= array[ right ] )
	{
	  sorted[ cursor ] = array[ left ];        instr_count++;
	  left++;         instr_count++;
	}
      else
	{
	  sorted[ cursor ] = array[ right ];        instr_count++;
	  right++;        instr_count++;
	}

      cursor++;         instr_count++;
    }

  instr_count++;
  if( left > mid)
    {
      while( right <= end )
	{
	  instr_count++;

	  sorted[ cursor ] = array[ right ];       instr_count++;
	  right++;       instr_count++;
	  cursor++;       instr_count++;
	}
    }
  else
    {
      while( left <= mid )
	{
	  instr_count++;
      
	  sorted[ cursor ] = array[ left ];        instr_count++;
	  left++;       instr_count++;
	  cursor++;       instr_count++;
	}
    }

  memcpy( &array[begin], &sorted[0], sizeof(int)*(end-begin+1));

  /*
  for( int i = 0; i < (end-begin+1); i++ ) {
      instr_count++;
      instr_count++;

    array[ begin+i ] = sorted[i];       instr_count++;
  }
  */
      instr_count++;
  delete[] sorted;
  return instr_count;
}

int merge_sort( int array[], int begin,int end )
{
  int instr_count = 1;
  int mid; 
  if( begin < end ) 
    {
      instr_count++;

      mid = begin + ((end-begin)/2); instr_count++;
      instr_count += merge_sort( array, begin, mid );
      instr_count += merge_sort( array, mid+1, end );
      instr_count += merge( array, begin, mid, end );
    }

  instr_count++;
  return instr_count;
}

bool test_merge( int tcount )
{
  bool success = true;
  srand( time( 0 ) );
  FILE* fp = fopen( "./merge.out", "wt" );
  if( !fp ) {
    cout << "failed to open output file merge.out" << endl;
    return false;
  }

  int trials[] = { 8, 17, 31, 43, 51, 60, 72, 79, 92, 100 };
  int trialcount = sizeof( trials ) / sizeof( trials[0] );

  for( int i = 0; i < tcount; i++ ) {

    //        int size = trials[i];
	    int size = 2*i;

    int* array = new int[ size ];

    for( int j = 0; j < size; j++ ) {
      array[ j ] = (rand()/(float)RAND_MAX) * 1000;
    }
    /*
    int count = merge_sort1( array, size, 0, size-1 );
    fprintf( fp1, "%d\t%d\n", size, count );

    if( size ) {
      int last = array[0];
      for( int j = 1; j < size; j++ ) {
	if( array[j] >= last ) {
	  last = array[j];
	} else {
	  cout << "sequence comparison failure on array: " << endl;
	  for( int p = 0; p < size; p++ )
	    cout << array[p] << " ";
	  cout << endl << "size=" << size << ", index=" << j << endl;
	  success = false;
	  break;
	}
      }
    }

    for( int j = 0; j < size; j++ ) {
      array[ j ] = (rand()/(float)RAND_MAX) * 10000;
    }
    */
    cout << "trial #" << i+1 << " before: ";
    for( int j = 0; j < size; j++ ) {
      cout << array[ j ] << " ";
    }
    cout << endl;

    unsigned int count2 = merge_sort( array, 0, size-1 );
    fprintf( fp, "%d\t%d\n", size, count2 );

    cout << "trial #" << i+1 << " after: ";
    for( int j = 0; j < size; j++ ) {
      cout << array[ j ] << " ";
    }
    cout << endl;

    if( size ) {
      int last = array[0];
      for( int j = 1; j < size; j++ ) {
	if( array[j] >= last ) {
	  last = array[j];
	} else {
	  cout << "sequence comparison failure on array: " << endl;
	  for( int p = 0; p < size; p++ )
	    cout << array[p] << " ";
	  cout << endl << "size=" << size << ", index=" << j << endl;
	  success = false;
	  break;
	}
      }
    }

    delete[] array;

    if( !success ) {
      break;
    }
  }

  fclose( fp );

  return success;
}
int main( int argc, char** argv )
{
  if( argc < 2 ) {
    cout << "usage: sorts <trialcount>" << endl;
    return 1;
  }

  errno = 0;
  int trialcount = (int)atol(argv[1]);
  if( errno ) {
    cout << "atol conversion error: errno=" << errno << endl;
    return 1;
  }

  bool test_insertion_sort = false;
  bool test_merge_sort = false;

  for( int i = 0; i < argc; i++ ) {
    if( string( argv[i] ) == "-i" )
      test_insertion_sort = true;

    if( string( argv[i] ) == "-m" )
      test_merge_sort = true;
  }

  if( test_merge_sort ) {
    cout << "testing merge_sort with " << trialcount << " trials" << endl;
    if( test_merge( trialcount ) ) {
      cout << "passed" << endl;
    } else {
      cout << "failed" << endl;
    }
  }

  if( test_insertion_sort ) {
    cout << "testing insertion_sort with " << trialcount << " trials" << endl;
    if( test_insertion( trialcount ) ) {
      cout << "passed" << endl;
    } else {
      cout << "failed" << endl;
    }
  }

  return 0;
}

