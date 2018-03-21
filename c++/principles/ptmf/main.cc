#include <iostream>

using namespace std;

class blah
{
public:

    void doblah() { cout << "blah::doblah" << endl; }
};


void callblah( blah* b, void (blah::*ptr)() )
{
    (b->*ptr)();
}

int main( int argc, char** argv )
{
    blah b;
    callblah( &b, &blah::doblah );
    return 0;
}


