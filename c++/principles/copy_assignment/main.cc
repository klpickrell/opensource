#include <iostream>

using namespace std;

class Test
{
public:
    Test()
    {
        cout << "Called Test::Test()" << endl;
        value = 0;
    }

    Test( const Test& rhs )
    {
        cout << "Called Test::Test( const Test& )" << endl;
        value = rhs.value;
    }


private:

    int value;
};

int main( int argc, char** argv )
{
    Test t;
    Test t2( t );

    return 0;
}


