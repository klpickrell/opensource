#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "boost/bind.hpp"
#include "boost/function.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/shared_array.hpp"

#include "boost/assign/list_of.hpp"
#include "boost/assign/std/vector.hpp"

using namespace std;

void printstring( const std::string& val ) {
    cout << "printstring: " << val << endl;
}

void valueprintstring( string header, string val ) {
    cout << header << ": " << val << endl;
}

class myclass {
public:
    void printstring( const std::string& val ) {
        cout << "printstring: " << val << endl;
    }

    static void staticprintstring( const std::string& val ) {
        cout << "static printstring: " << val << endl;
    }
};

int main( int argc, char** argv )
{
    // make sure we know how to call bind
    boost::function< void() > myprinter = 
        boost::bind( printstring, "howdy" );

    myprinter();

    boost::function< void() > mystaticprinter = 
        boost::bind( &myclass::staticprintstring,
                     "static howdy" );

    mystaticprinter();

    boost::function< void() > myinstanceprinter = 
        boost::bind( &myclass::printstring, myclass(),
                     "howdy doo-dee" );

    myinstanceprinter();


    string thestring( "The Header" );
    boost::function< void( string ) > myvalueprinter =
        boost::bind( valueprintstring, boost::ref( thestring ), _1 );

    myvalueprinter( "The Body" );
    myvalueprinter( "The Body Electric" );


    // now do some cool stuff reading ints from a file and putting them in a vector
    {

        ifstream file( "ascii.txt" );
        istream_iterator<string> begin( file ), end;
        vector<int> ints;
        transform( begin, end,
                   back_inserter( ints ),
                   boost::lexical_cast<int, string> );

        copy( ints.begin(), ints.end(), ostream_iterator<int>( cout, "\n" ) );
    }


    {
        ofstream ofile( "binary.fil", ios::binary );
        vector<int> values;
        values = boost::assign::list_of(1)(2)(3)(4)(5);
        ofile.write( reinterpret_cast<char*>(&values[0]), values.size()*sizeof(int) );
    }

    {
        int word_size = sizeof(int);

        ifstream file( "binary.fil", ios::binary );
        file.seekg( 0, ios::end );
        int length = file.tellg();
        file.seekg( 0, ios::beg );

        length -= length % word_size; // normalize length to sizeof int

        boost::shared_array<char> buffer( new char[length] );
        file.read( buffer.get(), length );
        file.close();

        vector<int> ints( reinterpret_cast<int*>( buffer.get() ),
                          reinterpret_cast<int*>( buffer.get() ) + length/word_size );

        cout << "read " << ints.size() << " ints from binary file:" << endl;
        copy( ints.begin(), ints.end(), ostream_iterator<int>( cout, "\n" ) );
    }

    return 0;
}
