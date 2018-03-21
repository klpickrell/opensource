#include <iostream>

using namespace std;

class A
{
public:
  char bar() { return 'a'; }
  virtual int foo() { return 1; }
};

class B : public A
{
public:
  char bar() { return 'b'; }
  virtual int foo() { return 2; }
};

class C : public B
{
public:
  char bar() { return 'c'; }
  virtual int foo() { return 3; }
};

int main( int argc, char** argv )
{
  A a;
  B b;
  C c;

  A* ab = &b;
  A* ac = &c;
  
  cout << a.foo() << endl;
  cout << ab->foo() << endl;
  cout << ac->foo() << endl;
  cout << a.bar() << endl;
  cout << ((A)b).bar() << endl;
  cout << ((A)c).bar() << endl;

  return 0;
}


