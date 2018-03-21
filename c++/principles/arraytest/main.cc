#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
  const char* strs[3];
  strs[0] = "howdy";
  strs[1] = "doody";
  strs[2] = "dandy";
  for( int i = 0; i < 3; i++ ) {
    cout << strs[i] << endl;
  }
  
  return 0;
}


