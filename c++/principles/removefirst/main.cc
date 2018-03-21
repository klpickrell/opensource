#include <iostream>

using namespace std;

void swap( int* a, int* b ) {
  int& ar = (*a);
  int& br = (*b);

  ar^=br; br^=ar; ar^=br;
}

void RemoveFirst( int a[], int& N, int x ) {

  bool removed = false;
  for( int i = 0; i < N; i++ ) {

    if( removed ) {
      swap( &a[i], &a[i-1] );
    }

    if( a[i] == x ) {
      removed = true;
    }
  }

  if( removed ) {
    N--;
  }
}


int main( int argc, char** argv )
{
  int a[] = { 1, 2, 4, 4, 5, 6, 8, 4 };
  int asize = sizeof( a ) / sizeof( a[0] );

  cout << "Before: ";
  for( int i = 0; i < asize; i++ ) {
    cout << " " << a[i];
  }
  cout << endl;

  RemoveFirst( a, asize, 4 );

  cout << "After: ";
  for( int i = 0; i < asize; i++ ) {
    cout << " " << a[i];
  }
  cout << endl;

  return 0;
}


