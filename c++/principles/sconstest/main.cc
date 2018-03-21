#include <iostream>
#include <boost/signals.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

void notify( int i ) 
{
    cout << "notify: " << i << endl;
}

int main( int argc, char** argv )
{
    boost::shared_ptr<int> i(new int(5));
    cout << "Hello SCons world!" << endl;

    boost::signal< void( int ) > sig;
    sig.connect( &notify );

    sig( *i );

    return 0;
}


