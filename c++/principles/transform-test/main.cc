#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <boost/assign/std/vector.hpp>

using namespace std;
using namespace boost::assign;

int main( int argc, char** argv )
{
    vector<int> a;
    a += 1,2,3,4,5;

    vector<int> b;
    b += 1,2,3,4;//,5,6,7;

    vector<int> c;

    cout << "a contains" << endl;
    copy( a.begin(), a.end(), ostream_iterator<int>( cout, " " ) );
    cout << endl;
    cout << "b contains" << endl;
    copy( b.begin(), b.end(), ostream_iterator<int>( cout, " " ) );
    cout << endl;

    std::transform( a.begin(), a.end(),
                    back_inserter( c ), std::negate<int>() );

    cout << "c contains" << endl;
    copy( c.begin(), c.end(), ostream_iterator<int>( cout, " " ) );
    cout << endl;

    return 0;
}


