#include <iostream>

using namespace std;

void reverse_inplace( int start, int N, int a[] )
{
  if( start < N-1 ) {
    a[start] ^= a[N-1]; a[N-1] ^= a[start]; a[start] ^= a[N-1];
    reverse_inplace( start+1, N-1, a );
  }
}

int main( int argc, char** argv )
{
  int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int vals_size = sizeof( vals ) / sizeof( vals[0] );

  for( int i = 0; i < vals_size; i++ ) {
    cout << vals[i] << " ";
  }

  cout << endl;
  
  reverse_inplace( 0, 5, vals );

  for( int i = 0; i < vals_size; i++ ) {
    cout << vals[i] << " ";
  }

  cout << endl;


  return 0;
}


