#include <stdlib.h>

#include <stdexcept>
#include <iostream>

using namespace std;

int compute( int a ) throw( out_of_range ) {

  if( a <= 0 ) {
    throw out_of_range( "value too small" );
  }

  return 5/a;
}

int main( int argc, char** argv )
{
  if( argc < 2 ) {
    cout << "usage: exctest <value>" << endl;
    return 0;
  }

  try { 
    long a = atol( argv[1] );
    cout << "Value:  " << compute( a ) << endl;
  } catch( out_of_range& e ) {
    cout << "Exception encountered: " << e.what() << endl;
  }

  return 0;
}


