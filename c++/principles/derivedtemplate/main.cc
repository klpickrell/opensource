#include <iostream>

using namespace std;

template< typename T >
class caller
{
public:
    caller( T ) {
        cout << "got a " << typeid( T ).name() << endl;
    }
};

class Base
{
public:
    
    virtual ~Base() {}

    class subclass
    {
    public:
        subclass() {
            cout << "Made a subclass: " << typeid( *this ).name() << endl;
        }
    };
};

class Derived1 : public Base
{
};

class Derived2 : public Base
{
};

int main( int argc, char** argv )
{
    Derived1::subclass s;
    caller< Derived1::subclass > caller( s );

    Derived2::subclass s2;
    caller< Derived2::subclass > caller2( s2 );

    return 0;
}
