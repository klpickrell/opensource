#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;


int main( int argc, char** argv )
{
  
  long width = 20;
  long precision = 10;

  if( argc > 1 ) {
    width = atol( argv[1] );
    cout << "setting width to " << width << endl;

    if( argc > 2 ) {
      precision = atol( argv[2] );
      cout << "setting precision to " << precision << endl;
    }
  }

  const char* exp = "5.999999e9";

  double dval = atof( exp );
  long l = atol( exp );
  
  cout << setw(width) << setprecision(precision) << dval << endl;

  return 0;
}


