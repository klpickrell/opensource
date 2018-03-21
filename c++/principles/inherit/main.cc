#include <iostream>
#include <string>
#include <memory>

using namespace std;

class A {
public:
  A() { _acount++; _id = _acount; }

  void printit() { cout << "Thanks for calling: " << _id << endl; }

  static int _acount;
  int _id;
};

int A::_acount = 0;

class service {
public:
  auto_ptr< A > _mya;
};

int main( int argc, char** argv )
{

  service s;
  s._mya.reset( new A );

  A a2 = *s._mya.get();
  a2.printit();

  return 0;
}


