#include <iostream>

using namespace std;

class Base
{
public:

    void funky( int a ) { cout << "Base::funky( int )" << endl; }
    void funky( string a ) { cout << "Base::funky( string )" << endl; }

    virtual void monkey( int a ) { cout << "Base::monkey( int )" << endl; }
    virtual void monkey( string a ) { cout << "Base::monkey( string )" << endl; }

};


class Derived : public Base
{
public:
    void monkey( string a ) { cout << "Derived::monkey( string )" << endl; }    
};


int main( int argc, char** argv )
{
    Derived d;
    d.funky( 10 );
    d.funky( "howdy" );
    d.monkey( "howdy" );
    d.monkey( 10 );



  return 0;
}


