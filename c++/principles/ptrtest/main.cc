#include <iostream>

using namespace std;

typedef int* pint;

void blah( pint* p ) {
  cout << "blah called with " << *p << endl;
}
int main( int argc, char** argv )
{
  int a = 10;
  pint b = &a;

  blah( b  );

  return 0;
}


