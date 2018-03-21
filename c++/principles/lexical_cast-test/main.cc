#include <iostream>
#include <sstream>
#include <iomanip>

#include <boost/lexical_cast.hpp>

using namespace std;

void printit( double d )
{
    cout << "printit: " << d << endl;
}

int main( int argc, char** argv )
{
    string s;
    cout << "enter double value:";
    cin >> s;
    printit( boost::lexical_cast<double>(s) );
    cout << endl << "enter hex value:";
    cin >> s;
//    printit( boost::lexical_cast<int>(s) );
    cout << endl << "attempting stringstream" << endl;
    stringstream ss;
    ss << hex << s;
    cout << ss.str() << endl;

    unsigned int val;
    if( ss >> val ) {
        cout << "insertion worked: " << val << endl;
    } else {
        cout << "insertion failed" << endl;
    }

    return 0;
}


