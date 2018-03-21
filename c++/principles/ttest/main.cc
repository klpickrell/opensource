#include "ttest.h"
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
  mytemp<int> mt;
  mytemp<int>::inner i = mt.doit( 20 );

  cout << "inner is " << i.myt << endl;
  
  return 0;
}


