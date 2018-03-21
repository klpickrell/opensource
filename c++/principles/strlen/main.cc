#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void test( const char* str )
{
  ostringstream os;
  os << "string length of str: " << strlen( str ) << endl;
  cout << os.str();
}


int main( int argc, char** argv )
{
  test( (const char*)"" );
  
  vector< int > test;

  for( int i = 0; i < 10; i++ )
    {
      cout << "adding something" << endl;
      test.push_back( i );
    }

  return 0;
}


