#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/ref.hpp>

using namespace std;

int main( int, char** )
{
    string thestring( "this      is     string   \t that shall rule      \tthe world" );

    typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep;
    tokenizer tokens(thestring, sep);
    copy( tokens.begin(), tokens.end(), ostream_iterator<string>( cout, " " ) );
    cout << endl;
}
