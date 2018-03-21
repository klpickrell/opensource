#include <memory>
#include <iostream>

using namespace std;

class FunkyOne {
public:
  FunkyOne( int i ) {
    _i = i;
    cout << "Created a FunkyOne!: " << _i << endl;
  }

  void doit() const {
    cout << "FunkyOne::doit _i is " << _i << endl;
  }

  ~FunkyOne() {
    cout << "Deleted a FunkyOne!" << endl;
  }

private:

  int _i;
};

class FunkyTwo {
public:
  FunkyTwo() {
    cout << "Created a FunkyTwo!" << endl;
  }

  void doit() const {
    cout << "FunkyTwo::doit" << endl;
  }

  ~FunkyTwo() {
    cout << "Deleted a FunkyTwo!" << endl;
  }
};

int main( int argc, char** argv )
{

  auto_ptr< FunkyOne > p( new FunkyOne( 5 ) );

  p->doit();

  auto_ptr< FunkyOne > p2;

  p2 = p;

  p2->doit();

  auto_ptr< FunkyTwo > p3( new FunkyTwo() );

  p3->doit();

  return 0;
}


