#include <iostream>

using namespace std;

class TestClass
{
public:
    TestClass( const string& id ) :
        id( id )
    {}

    void doit() const 
    {
        static int only = 0;
        only++;
        cout << "TestClass id=" << id << ", only=" << only << endl;
    }

    string id;
};

int main( int argc, char** argv )
{
    TestClass thing1( "thing1" );
    TestClass thing2( "thing2" );
    thing1.doit(); thing2.doit();
    thing1.doit(); thing2.doit();
    
    return 0;
}
