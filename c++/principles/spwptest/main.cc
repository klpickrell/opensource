#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

using namespace std;

int main( int, char** )
{
    boost::weak_ptr<int> w;
    {
        boost::shared_ptr<int> myint( new int(5) );
        w = myint;
        if( w.lock() ) {
            cout << "w" << endl;
        } else {
            cout << "not w" << endl;
        }

        boost::shared_ptr<int> notw( w );
    }

//    boost::shared_ptr<int> notw( w );
    if( w.lock() ) {
        cout << "w" << endl;
    } else {
        cout << "not w" << endl;
    }

    return 0;
}
