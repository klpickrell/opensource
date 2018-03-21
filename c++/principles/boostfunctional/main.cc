#include "boost/bind.hpp"
#include "boost/function.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class status
{
public:
    status( const string& msg, bool ok = true ) :
        _msg( msg ),
        _ok( ok )
    {}

    bool ok() const { return _ok; }
    void report() const { cout << "msg is " << _msg << endl; }

    void break_it() { _ok = false; }

private:

    string _msg;
    bool _ok;
};

class print_formatted
{
public:
    print_formatted( const string& value ) :
        _value( value ) {}


    void operator()( const string& message ) 
    {
        cout << _value << message << endl;
    }

    typedef void result_type;

private:
    
    string _value;
};

void someargs1( int a )
{
    //    cout << "someargs1 called" << endl;
    cout << "someargs1 called with a=" << a << endl;
}

void someargs( string a, int b, vector< int > c )
{
    cout << "someargs called with a=" << a << ", b=" << b << ", c=[ ";
    for( vector< int >::iterator it = c.begin();
         it != c.end();
         it++ ) {
        cout << (*it) << " ";
    }

    cout << "]" << endl;
}

int main( int argc, char** argv )
{

    vector< int > c;
    c.push_back( 1 );
    c.push_back( 2 );
    c.push_back( 3 );

    //    boost::bind( &someargs, string( "thing" ), 5, c )();

    boost::function< void ( string ) > f = boost::bind( &someargs, _1, 5, c );
    
    //    boost::function< void () > f2 = boost::bind( &someargs1, 3 );

    //    if( f2 ) {
    //        f2();
    //    }
    if( f ) {
        cout << "calling f" << endl;
        f( "howdy" );

        cout << "calling f" << endl;
        f( "doody" );
    }
    cout << "done" << endl;

    
    vector< status* > statuses;
    statuses.push_back( new status( "A OK" ) );
    statuses.push_back( new status( "NOT OK", false ) );

    for_each( statuses.begin(), statuses.end(),
              boost::bind( &status::report, _1 ) );


    boost::bind( print_formatted( "Header: " ), _1 )( "message" );

    vector< string > messages;
    messages.push_back( "message1" );
    messages.push_back( "message2" );
    messages.push_back( "message3" );

    for_each( messages.begin(),
              messages.end(),
              boost::bind<void>( print_formatted("Header:"),
                                 _1 ) );


    vector< double > values;
    values.push_back( 10.0 );
    values.push_back( 100.0 );
    values.push_back( 1000.0 );

    std::transform( values.begin(),
                    values.end(),
                    values.begin(),
                    boost::bind( std::multiplies< double >(), 0.90,
                                 boost::bind< double >( std::multiplies< double >(), _1, 1.10 ) ) );

    std::copy( values.begin(), values.end(), ostream_iterator<double>( std::cout, "\n" ) );

    return 0;
}
