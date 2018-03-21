#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main( int argc, char** argv )
{
    vector<int> v1;
    vector<int> v2;

    v2.push_back( 333);

    for( int i = 0; i < 10; i++ ) {
        v1.push_back( i );
    }

    copy( v1.begin(), v1.end(), back_inserter(v2) );

    copy( v2.begin(),
          v2.end(),
          ostream_iterator<int>( cout, "," ) );
    
    cout << endl;
    
    return 0;
}


