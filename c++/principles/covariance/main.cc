#include <iostream>

using namespace std;

class A;
class B;

class Base
{
public:

    virtual A* doit() { cout << "Base::doit" << endl; return a; }

private:
    A* a;
};

class Derived : public Base
{
public:
    
    B* doit() { cout << "Derived::doit" << endl; return b; }

private:
    B* b;
};

class A
{
public:
    A() { cout << "A::A" << endl; }
};

class B : public A
{
public:
    B() { cout << "B::B" << endl; }
};


int main( int argc, char** argv )
{
    Base* base = new Derived;
    A* b = base->doit();
    delete b;
    delete base;
    return 0;
}


