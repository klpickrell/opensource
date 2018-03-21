#include <iostream>
#include <sstream>

using namespace std;

class StaticFuncBase
{
public:

  static virtual bool got_one() { cout << "StaticFuncBase::got_one" << endl; return true; }
};

class StaticFuncDerived : public StaticFuncBase
{
public:

  bool got_one() { cout << "StaticFuncDerived::got_one" << endl; return true; }
};

int main( int argc, char** argv )
{
  StaticFuncBase* b = new StaticFuncBase();
  StaticFuncBase* c = new StaticFuncDerived();

  b->got_one();
  c->got_one();

  return 0;
}


