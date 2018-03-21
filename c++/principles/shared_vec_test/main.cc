#include <iostream>
#include <vector>
#include "boost/shared_ptr.hpp"

using namespace std;

class Foo
{
public:
    Foo( int val ) :
        val( val )
    {}

public:
    void bar() const { cout << "Foo::bar " << val << endl; }

private:
    int val;
};


int main( int argc, char** argv )
{
    vector<boost::shared_ptr<Foo> > foos;
    foos.push_back( boost::shared_ptr< Foo >( new Foo( 1 ) ) );
    foos.push_back( boost::shared_ptr< Foo >( new Foo( 2 ) ) );
    foos.push_back( boost::shared_ptr< Foo >( new Foo( 3 ) ) );

    for( vector< boost::shared_ptr<Foo> >::iterator it = foos.begin();
         it != foos.end();
         ++it ) {

        it->bar();
    }

    return 0;
}
