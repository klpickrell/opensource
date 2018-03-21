#include <iostream>
#include <boost/xpressive/xpressive.hpp>

namespace bx = boost::xpressive;
using namespace std;
int main( int argc, char** argv )
{
    string hello( "hello world!" );

    bx::sregex rex = bx::sregex::compile( "(\\w+) (\\w+)!" );
    bx::smatch what;

    if( bx::regex_match( hello, what, rex ) )
    {
        cout << what[0] << '\n'; // whole match
        cout << what[1] << '\n'; // first capture
        cout << what[2] << '\n'; // second capture
    }

    return 0;
}


