#include <iostream>

using namespace std;

template< typename T >
class closure
{
public:

    closure( T t ) :
        _t( t ) {}

    template< typename N >
    bool call( N n ) {
        return n( _t );
    }

private:
    T _t;
};

class callable
{
public:

    template< typename N >
    bool operator()( N n ){ cout << "callable::operator() N=" << n << endl; }
};



int main( int argc, char** argv )
{
    callable c;
    closure< int > cl( 5 );

    cl.call< callable >( c );

    return 0;
}


