#include "boost/spirit/core.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;
using namespace boost::spirit;

int main( int argc, char** argv )
{
    vector<int> ints;
    
    string line;
    cin >> line;

    cout << "you entered: " << line << endl;

    parse( line, (real_p << *( ch_p(',') << real_p ) ) );

    copy( ints.begin(), ints.end(), ostream_iterator<int>( cout, ":" ) );
    
    return 0;
}


