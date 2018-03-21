#include <iostream>
using namespace std;
void swap( int* a, int* b )
{
  int& ar = (*a);
  int& br = (*b);
  ar^=br; br^=ar; ar^=br;
}
void Delete( int a[], int& N, int TARGET )
{
  int i;
  int count = 0;
  for( i = 0; i < N; i++ ) {
    if( a[i] == TARGET ) {
      count++;
      continue;
    }

    if( count ) {
      swap( &a[i], &a[i-count] );
    }
  }

  N -= count;
}

int main( int argc, char** argv )
{
  int eg[] = { 1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9 };

  int sze = sizeof( eg )/sizeof( eg[0] );
  
  cout << sze << endl;

  cout << "before: ";
  for( int i = 0; i < sze; i++ ) {
    cout << eg[i] << " ";
  }
  cout << endl;

  Delete( eg, sze, 5 );

  cout << "after: ";
  for( int i = 0; i < sze; i++ ) {
    cout << eg[i] << " ";
  }
  cout << endl;


  return 0;
}


