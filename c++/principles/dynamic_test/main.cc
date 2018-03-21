#include <iostream>

using namespace std;

class Base
{
public:
    //    Base() { cout << "Base::Base" << endl; }
    virtual ~Base() { cout << "Base::~Base" << endl; }

    virtual void update() = 0;
};

class Derived1 : public Base
{
public:
    //    Derived1() { cout << "Derived1::Derived1" << endl; }
    //    virtual ~Derived1() { cout << "Derived1::~Derived1" << endl; }

    virtual void reset() = 0;
};

class Derived2 : public Derived1
{
public:
    Derived2() { cout << "Derived2::Derived2" << endl; }
    virtual ~Derived2() { cout << "Derived2::~Derived2" << endl; }

    void reset() { cout << "Derived2::reset" << endl; }
    void update() { cout << "Derived2::update" << endl; }
};

int main( int argc, char** argv )
{
    Base* b1 = new Derived2;
    Derived1* d = dynamic_cast< Derived1* >( b1 );
    if( d == 0 ) {
        cout << "dynamic_cast< Derived1* >( b1 ) failure" << endl;
    } else {
        cout << "dynamic_cast< Derived1* >( b1 ) success" << endl;
        d->reset();
        d->update();
    }

    return 0;
}


