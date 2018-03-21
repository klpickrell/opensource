#include <iostream>
#include "mytemplate.h"

using namespace std;

class One {
public:
  
  One( const string& rval ) {
    _id = rval;
  }
  
  void doit() const {
    cout << "One::doit! _id=" << _id << endl;
  }

  string id() const { return _id; }

private:

  string _id;
};

class Two {
public:
  
  Two( const string& rval ) {
    _id = rval;
  }
  
  void doit() const {
    cout << "Two::doit! _id=" << _id << endl;
  }

  string id() const { return _id; }

private:

  string _id;
};


int main( int argc, char** argv )
{
  
  HasAMap< One > OneMap;
  HasAMap< Two > TwoMap;

  OneMap.add( new One( "One1" ) );
  OneMap.add( new One( "One2" ) );

  One* o = OneMap.get( "One1" );
  o->doit();
  
  return 0;
}


