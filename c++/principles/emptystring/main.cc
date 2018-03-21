#include <string>
#include <iostream>

#include <map>
#include <set>

using namespace std;

int main( int argc, char** argv )
{
    //    char* buf = "";
    //    string s( 0 );
    
    //    cout << "The String:" << s << ":" << endl;

    typedef map< string, set<int> > SMap;


    SMap mymap;

    mymap[ "thing1" ].insert( 1 );
    mymap[ "thing1" ].insert( 2 );
    mymap[ "thing1" ].insert( 3 );

    mymap[ "thing2" ].insert( 4 );
    mymap[ "thing2" ].insert( 5 );
    mymap[ "thing2" ].insert( 6 );

    SMap::iterator it = mymap.find( string() );
    if( it == mymap.end() ) {
        cout << "it is end" << endl;
    } else {
        cout << "it is not end" << endl;
    }

    it = mymap.find( "thing1" );
    if( it == mymap.end() ) {
        cout << "it is end" << endl;
    } else {
        cout << "it is not end" << endl;
    }

    cout << "size=" << mymap[ "thing1" ].size() << endl;
    for( set< int >::iterator it = mymap["thing1"].begin();
         it != mymap[ "thing1" ].end();
         it++ ) {
        cout << *it << endl;
    }
    
    mymap[ "thing1" ].erase( 1 );
    mymap[ "thing1" ].erase( 2 );
    mymap[ "thing1" ].erase( 3 );

    cout << "size=" << mymap[ "thing1" ].size() << endl;
    for( set< int >::iterator it = mymap["thing1"].begin();
         it != mymap[ "thing1" ].end();
         it++ ) {
        cout << *it << endl;
    }

    mymap[ "thing1" ].insert( 5 );
    mymap[ "thing1" ].insert( 5 );
    mymap[ "thing1" ].insert( 5 );
    cout << "size=" << mymap[ "thing1" ].size() << endl;
    for( set< int >::iterator it = mymap["thing1"].begin();
         it != mymap[ "thing1" ].end();
         it++ ) {
        cout << *it << endl;
    }

    return 0;
}


