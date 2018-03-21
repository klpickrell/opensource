#include <iostream>
#include "boost/weak_ptr.hpp"

using namespace std;

int main( int argc, char** argv )
{
    boost::shared_ptr< int > p1( new int( 10 ) );

    cout << "p1 contains: " << (*p1) << endl;

    cout << "making a weak_ptr..." << endl;

    boost::weak_ptr< int > p2( p1 );

    if( !p2.expired() ) {
        cout << "p2 is valid" << endl;
    } else {
        cout << "p2 is invalid" << endl;
    }

    cout << "resetting p1" << endl;
    p1.reset( new int( 20 ) );
    cout << "p1 contains: " << (*p1) << endl;

    if( !p2.expired() ) {
        cout << "p2 is valid" << endl;
    } else {
        cout << "p2 is invalid" << endl;
    }

    


    return 0;
}


