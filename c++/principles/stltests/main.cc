#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

int main( int argc, char** argv )
{
    list< int > cont1;
    for( int i = (int)'A'; i < (int)'Z'; i++ ) {
        cont1.push_back( i );
    }


    vector< int > cont2;
    string cont3;

    copy( cont1.begin(), cont1.end(),
          back_inserter( cont2 ) );

    copy( cont1.begin(), cont1.end(),
          inserter( cont3, cont3.end() ) );
    
    copy( cont1.begin(), cont1.end(),
          ostream_iterator< int >( cout, "\n" ) );

    copy( cont3.begin(), cont3.end(),
          ostream_iterator< char >( cout ) );

    cout << endl;

    return 0;
}


