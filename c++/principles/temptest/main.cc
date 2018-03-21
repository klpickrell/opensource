#include <iostream>
#include "boost/shared_ptr.hpp"
#include "SOIFactory.h"

using namespace boost;

using namespace std;

/*
class anotherbase
{
public:
    anotherbase() { cout << "anotherbase::anotherbase" << endl; }
};

class another : public anotherbase
{
public:
    another() { cout << "another::another" << endl; }
};


class madeup
{
private:

    template< typename T > shared_ptr< anotherbase > func1() {
        cout << "func1" << endl;
        return shared_ptr< anotherbase >( new T );
    }

    template< typename T > void func2() {
        cout << "func2" << endl;
        func1< T >();
    }

public:

    void doit() {
        
        cout << "calling func2" << endl;
        func2< another >();
    }


};
*/

int main( int argc, char** argv )
{
    SOIFactory::instance();
    return 0;
}


