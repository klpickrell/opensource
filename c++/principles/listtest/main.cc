#include <iostream>
#include <list>

using namespace std;

int main( int argc, char** argv )
{
    list< int > l;
    for( int i = 0; i < 10; i++ )
        l.push_back( i );

    cout << "num elements in list is " << l.end() - l.begin() << endl;
    
    return 0;
}


