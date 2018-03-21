#include <iostream>
#include <stdexcept>

using namespace std;

int max( int a[], int N ) throw( out_of_range ) {
  if( N <= 0 ) {
    throw out_of_range( "Array index out of bounds" );
  }

  int max_val = a[0];
  for( int i = 1; i < N; i++ ) {
    if( a[i] > max_val ) {
      max_val = a[i];
    }
  }
  
  return max_val;
}

int main( int argc, char** argv )
{
  int vals[] = { 1, 2, 5, 7, 9, 20, 25, 3, 7, 9 };
  int size = sizeof( vals ) / sizeof( vals[0] );

  int max_val;
  try {
    max_val = max( vals, 0 );
    cout << "maximum value of array is " << max_val << endl;
  } catch( out_of_range& e ) {
    cout << "exception encountered while checking max: " << e.what() << ", " << typeid( e ).name() <<  endl;
  }

  return 0;
}


