#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
  cout << "allocating new( nothrow )" << endl;
  int* a = new( nothrow ) int[ 100 ];
  a[0] = 10;
  a[99] = 100;
  
  cout << "deleting new( nothrow )" << endl;
  delete[] a;

  return 0;
}


