#include <iostream>
#include "boost/shared_ptr.hpp"

using namespace std;


class base
{
public:
    base() { _terminate = false; }

    virtual void terminate() { _terminate = true; }

public:

    bool _terminate;

};

class derived : public base
{
public:

    void terminate() { cout << "derived2 terminate" << endl; _terminate = true; }

public:

    bool _terminate;
};

class derived2 : public derived {};

int main( int argc, char** argv )
{
    
    derived d;
    derived2 d2;
    
    cout << "base::_terminate=" << &d2.base::_terminate << ", derived::_terminate=" << &d2.derived::_terminate << endl;
    cout << "derived2._terminate=" << &d2._terminate << endl;


    boost::shared_ptr<base> b( new derived2 );
    
    boost::shared_ptr<derived2> der = boost::dynamic_pointer_cast<derived2>(b);
    der->terminate();

    return 0;
}


