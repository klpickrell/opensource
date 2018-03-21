#include <iomanip>
#include <sstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef vector< double > myvectortype;

int main( int argc, char** argv )
{
  cout << "creating vector of doubles... " << endl;
  myvectortype vint;

  cout << "adding 1-10 to myvectortype..." << endl;

  for( int i = 1; i <= 10; i++ ) {
    ostringstream sstr;
    sstr << setprecision( 20 ) << "adding " << i << " to vector..." << endl;
    cout << sstr.str();

    vint.push_back( i );
  }

  cout << "our vector contains:" << endl;

  for( myvectortype::iterator ix = vint.begin();
       ix != vint.end();
       ix++ )
    {
      ostringstream sstr;
      sstr << setprecision( 20 ) << *(ix) << endl;
      cout << sstr.str();
    }

  list< int > intlist;
  for( int i = 0; i < 10; i++ )
    {
      intlist.push_back( i );
    }
  
  ostringstream sstr;
  sstr << "list count is " << intlist.size() << endl;
  cout << sstr.str();
  return 0;
}


