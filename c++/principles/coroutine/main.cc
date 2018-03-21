#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int generator()
{
  static int state = 0;
  static int count;
  switch( state )
    {

    case 0:
      for( count=1; count < 10; count++ ) {
	state = 1;
	return count;
        case 1:
	  {
	    int i = 5;
	    i++;
	  }
      }
    }
}


int main( int argc, char** argv )
{
  /*
  for( int i = 0; i < 20; i++ ) {
    ostringstream os;
    os << "generator now returns: " << generator() << endl;
    cout << os.str();
    }*/
   char buf[256];
   sprintf( buf, "start dc{ freqMHz=%f };", 87.777777 );

   cout << "old=" << buf << endl;

   sprintf( buf, "start dc{ freqMHz=%.4f };", 87.777777 );

   cout << "new=" << buf << endl;

  ostringstream os;

  double freq = 87.777777;

  os << "freq=" << freq << endl;
  
  os << setprecision( 20 ) << "set precision freq=" << freq << endl;

  cout << os.str();

  return 0;
}


