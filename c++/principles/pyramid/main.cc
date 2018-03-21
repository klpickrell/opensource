#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <errno.h>

using namespace std;

void printpyramid( int numrows ) {

  int width = 2*numrows-1;
  for( int i = 1; i <= numrows; i++ ) {
    
    for( int j = 0; j < (width - (2*i-1))/2; j++ )
      cout << " ";

    for( int j = 0; j < (2*i-1); j++ )
      cout << "*";

    for( int j = 0; j < (width - (2*i-1))/2; j++ )
      cout << " ";

    cout << endl;
  }
}

int main( int argc, char** argv )
{
  if( argc < 2 ) {
    cout << "usage: printpyramid [numrows]" << endl;
    return -1;
  }

  errno = 0;
  long lval = atol( argv[1] );

  if( errno ) {
    cout << "error converting '" << argv[1] << "' to integer" << endl;
    return -1;
  } else {
    cout << "printing pyramid with " << lval << " rows" << endl;
  }

  printpyramid( lval );

  return 0;
}


