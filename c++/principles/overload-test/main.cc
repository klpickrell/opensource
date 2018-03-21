#include <iostream>

using namespace std;

class Base
{
public:
    template< typename T >
    void push( const T& t ) const { cout << "Base::push( T ): " << t << endl; }
    void push() const { cout << "Base::push()" << endl; }
    void push( int ) const { cout << "Base::push( int )" << endl; }
};


class Derived : public Base
{
public:
    using Base::push;
    void push() const { cout << "Derived::push" << endl; Base::push<int>( 5 ); }
};

int main( int argc, char** argv )
{
    
    Derived d;
    d.push();
    d.push<float>(3.14);

    return 0;
}


