#include <iostream>
#include <boost/shared_ptr.hpp>
#include <vector>

#include "MyIter.h"

using namespace std;

class Funky
{
public:
    Funky() {
        cout << "Funky::Funky" << endl;
    }

    void shoutout() const {
        cout << "Funky::shoutout gives all yall a shoutout" << endl;
    }
};

int main( int argc, char** argv )
{
    My my( "howdy" );
    Bonk b = my.getBonk();

    boost::shared_ptr<char> thestr( strndup( b.thestr, b.length ), free );

    cout << "b.length=" << b.length << ", b.thestr=" << thestr.get() << endl;

    vector< boost::shared_ptr< Funky > > funky;
    funky.push_back( boost::shared_ptr< Funky >( new Funky ) );
    funky.push_back( boost::shared_ptr< Funky >( new Funky ) );
    funky.push_back( boost::shared_ptr< Funky >( new Funky ) );
    funky.push_back( boost::shared_ptr< Funky >( new Funky ) );
    funky.push_back( boost::shared_ptr< Funky >( new Funky ) );


    for( vector< boost::shared_ptr<Funky> >::iterator i = funky.begin(); i != funky.end(); ++i ) {
        i->shoutout();
    }


    return 0;
}


