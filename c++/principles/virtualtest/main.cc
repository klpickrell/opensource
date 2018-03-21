#include <iostream>

using namespace std;

class Arg {
public:
    virtual ~Arg() {}
    virtual void doit() const { cout << "Arg::doit" << endl; }
};

class ConcreteArg : public Arg
{
public:
    void doit() const { cout << "ConcreteArg::doit" << endl; }
};

class Base {
public:
  Base() {
    cout << "Base::Base()" << endl;
  }

  virtual void reset( int arg ) {
    cout << "Base::reset( " << arg << " )" << endl;
    cout << "calling reset()..." << endl;
    reset();
  }

  virtual void reset() = 0;

  virtual void doit( Arg* arg ) const = 0;
};

class Derived1 : public Base {
public:
  Derived1() {
    cout << "Derived1::Derived1()" << endl;
  }
  
  virtual void reset() {
    cout << "Derived1::reset()" << endl;
  }

    void doit( Arg* arg ) const { arg->doit(); }
};

class Derived2 : public Base {
public:
  Derived2() {
      // extra line of code

    cout << "Derived2::Derived2()" << endl;
  }

  using Base::reset;
  virtual void reset() {
    cout << "Derived2::reset()" << endl;
  }

    using Base::doit;
    void doit( ConcreteArg* arg ) const { arg->doit(); }
};


class A
{
public:
    virtual void doit() const { cout << "A::doit" << endl; }
};

class B : public A
{
public:
    virtual void doit() const { cout << "B::doit" << endl; }
};

int main( int argc, char** argv )
{
  
    //  Derived2 d;
    //  d.reset( 10 );


    //  B b;
    //  b.doit();
    //  b.A::doit();

    Derived1 d1;
    Derived2 d2;

    Arg arg1;
    ConcreteArg arg2;
    
    d1.doit( &arg1 );
    d2.doit( &arg2 );
  
  return 0;
}


