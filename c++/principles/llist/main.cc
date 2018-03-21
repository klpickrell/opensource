#include <iostream>

using namespace std;

#include "linked_list.h"

int main( int argc, char** argv )
{
  linked_list< int > lint;
  for( int i = 0; i < 10; i++ ) {
    lint.add( i );
  }

  linked_list< int >::iterator it =lint.begin();
  while( it != lint.end() ) {
    cout << "it value: " << (*it) << endl;
    it++;
  }

  it = lint.begin();
  it++;
  it++;
  it++;

  lint.erase( it );

  it = lint.begin();

  cout << "erased..." << endl;
  while( it != lint.end() ) {
    cout << "it value: " << (*it) << endl;
    it++;
  }

  return 0;
}


