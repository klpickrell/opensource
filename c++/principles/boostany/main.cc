#include <iostream>
#include "boost/any.hpp"

using namespace std;


void printit( const boost::any& item, boost::any& ncitem )
{
    *(boost::any_cast<int>(&ncitem)) = 5;
    const int* a = boost::any_cast<int>(&item);
    try {
        if( a ) {
            cout << "its an int: " << *a << endl;
        }
    } catch( const boost::bad_any_cast& ex ) {
        cerr << ex.what() << endl;
    }

    try {
        cout << "its a string: " << boost::any_cast<string>(item) << endl;
    } catch( const boost::bad_any_cast& ex ) {
        cerr << ex.what() << endl;
    }
}

int main( int argc, char** argv )
{
    boost::any b = 10;
    cout << "b is " << boost::any_cast<int>(b) << endl;
    printit( string( "howdy" ), b );
    cout << "b is " << boost::any_cast<int>(b) << endl;
    printit( 5, b );

    return 0;
}


