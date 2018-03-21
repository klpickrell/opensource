#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <boost/tokenizer.hpp>

using namespace std;

int main( int /*argc*/, char** /*argv*/ )
{
    string thestring;
    thestring += "this is string 1\n";
    thestring += "this is string 2\n";
    thestring += "this is string 3\n";
    thestring += "this is string 4\n";

    typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep("\n");
    tokenizer tokens(thestring, sep);
    vector<string> myvec;
    copy( tokens.begin(), tokens.end(), back_inserter( myvec ) );

    cout << "vector now contains: " << endl;
    copy( myvec.begin(), myvec.end(), ostream_iterator<string>(cout, "\n") );
    
    return 0;
}
