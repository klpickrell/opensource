#include <time.h>
#include <stdlib.h>

#include <stdexcept>
#include <iostream>

using namespace std;

void bsort( int vals[], int N ) throw( out_of_range ) {

  if( N == 0 ) {
    return;
  } else if( N < 0 ) {
    throw out_of_range( "Array index out of bounds" );
  }

  for( int i = 0; i < N-1; i++ ) {

    bool swapped = false;
    for( int j = 1; j < N-i; j++ ) {
      if( vals[j-1] > vals[j] ) {
	vals[j-1] ^= vals[j]; vals[j] ^= vals[j-1]; vals[j-1] ^= vals[j];
	swapped = true;
      }
    }

    if( !swapped ) {
      cout << "array is sorted, returning" << endl;
      break;
    }

    cout << "i=" << i << ", array a contains: ";
    for( int i = 0; i < N; i++ ) {
      cout << vals[i] << " ";
    }
    cout << endl;
  }
}

int main( int argc, char** argv )
{

  srand( time(0) );

  int a[20];
  int alen = sizeof( a ) / sizeof( a[0] );

  for( int i = 0; i < alen; i++ ) {
    a[i] = int( float(rand()) / RAND_MAX * 100 );
  }

  cout << "pre array a contains: ";
  for( int i = 0; i < alen; i++ ) {
    cout << a[i] << " ";
  }
  cout << endl;

  bsort( a, alen );

  cout << "post array a contains: ";
  for( int i = 0; i < alen; i++ ) {
    cout << a[i] << " ";
  }
  cout << endl;

  cout << "validating sort...";
  
  bool sorted = true;
  for( int i = 0; i < alen-1; i++ ) {
    int min = a[i];
    for( int j = i + 1; j < alen; j++ ) {
      if( a[j] < min ) {
	cout << "fail" << endl;
	sorted = false;
	break;
      }
    }
    if( !sorted ) {
      break;
    }
  }

  if( sorted ) {
    cout << "pass" << endl;
  }

  return 0;
}


