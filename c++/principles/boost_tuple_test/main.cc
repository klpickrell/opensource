#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/tuple/tuple_comparison.hpp"

using namespace std;

namespace bt = boost::tuples;

int main( int argc, char** argv )
{
    
    bt::tuple<int,int,int> t0( 1,3,5 );
    bt::tuple<int,int,int> t1( 1,3,5 );
    bt::tuple<int,int,int> t2( 1,4,2 );


    cout << "exhibit a:" << endl;
    cout << t0 << t1 << t2 << endl;
    
    if( t0 == t1 ) {
        cout << t0 << "==" << t1 << endl;
    } else {
        cout << t0 << "!=" << t1 << endl;
    }

    if( t0 == t2 ) {
        cout << t0 << "==" << t2 << endl;
    } else {
        cout << t0 << "!=" << t2 << endl;
    }

    if( t0 < t1 ) {
        cout << t0 << "<" << t1 << endl;
    } else {
        cout << t0 << ">=" << t1 << endl;
    }

    if( t0 < t2 ) {
        cout << t0 << "<" << t2 << endl;
    } else {
        cout << t0 << ">=" << t2 << endl;
    }

    vector<bt::tuple<string,vector<string> > > vec;
    

    int arr1[] = { 1,2,3,4,5 };
    vector<int> v2( &arr1[0], &arr1[ sizeof(arr1)/sizeof(arr1[0]) ]  );

    std::copy( v2.begin(),v2.end(),
               ostream_iterator<int>( cout, "," ) );

    char* arr[] = { "howdy", "do", "to", "you", "and", "yours" };

    vector<string> v( arr, arr + sizeof( arr )/sizeof( arr[0] ) );

    vec.push_back( bt::make_tuple( "the thing", v ) );
    vec.push_back( bt::make_tuple( "the other thing", v ) );

    for( vector< bt::tuple<string,vector<string> > >::iterator v = vec.begin();
         v != vec.end();
         ++v ) {
        
        cout << v->get<0>() << endl;
        for( vector<string>::iterator s = v->get<1>().begin();
             s != v->get<1>().end();
             ++s ) {
            cout << "--->" << *s << endl;
        }
    }

    return 0;
}


