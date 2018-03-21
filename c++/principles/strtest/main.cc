#include "boost/shared_ptr.hpp"

#include <iostream>
#include <string.h>

using namespace std;

int main( int argc, char** argv )
{
    char buf[] = { 0xFF, 0xFE, 0xFF, 0xFD };
    
    boost::shared_ptr<char> sync( strndup( buf, 4 ),
                                  free );

    if( string( sync.get() ) == "\xFF\xFE\xFF\xFE" ) {
        cout << "equal" << endl;
    } else {
        cout << "not equal" << endl;
    }

    return 0;
}


