#include <iostream>

using namespace std;

class SOI
{
    
};

class A
{

public:

    const SOI& getsoi() const { cout << "called: const SOI& getsoi() const" << endl; return soi; }
    SOI& getsoi() { cout << "called: SOI& getsoi" << endl; return soi; }

    SOI soi;
};


void takesoi( const SOI& soi ) {
    cout << "called void takesoi( const SOI& soi )" << endl;
}

int main( int argc, char** argv )
{
    cout << "creating A" << endl;
    A a;
    SOI& soi = a.getsoi();
    const SOI& csoi = a.getsoi();

    const A ca = A();

    takesoi( a.getsoi() );
    takesoi( ca.getsoi() );

    return 0;
}


