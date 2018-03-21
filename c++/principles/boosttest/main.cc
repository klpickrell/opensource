#include <vector>
#include <iostream>
#include <algorithm>
#include "boost/bind.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/shared_ptr.hpp"

using namespace std;

int main( int argc, char** argv )
{
    //    boost::scoped_ptr< int > p( new int( 10 ) );
    //    boost::scoped_ptr< int > b( new int( 5 ) );
    
    //    cout << "(*p)=" << (*p) << ", (*b)=" << (*b) << endl;

    /*
    boost::shared_ptr< int > p( new int( 10 ) );
    boost::shared_ptr< int > p2( p );

    cout << "(*p)=" << (*p) << ", (*p2)=" << (*p2) << endl;

    p.reset( new int( 5 ) );

    cout << "(*p)=" << (*p) << ", (*p2)=" << (*p2) << endl;

    p.reset();
    
    if( p ) {
        cout << "p is valid" << endl;
    } else {
        cout << "p is not valid" << endl;
    }
    */

    
    return 0;
}


