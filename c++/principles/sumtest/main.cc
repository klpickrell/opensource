#include <iostream>
#include <vector>

using namespace std;

unsigned long long sum( const vector< int >& vals )
{
    unsigned long long thesum = 0;
    for( int i = 0; i < vals.size(); i++ ) {
        thesum += vals[i];
    }
    return thesum;
}

unsigned long long sum_dc( const vector< int >& vals, int begin, int end )
{
    if( begin >= end ) {
        return vals[begin];
    }

    unsigned long long thesuml = sum_dc( vals, begin, end/2 );
    unsigned long long thesumr = sum_dc( vals, end/2+1, end );
    return thesuml + thesumr;
}


int main( int argc, char** argv )
{
    vector< int > vals;

    const int count = 10;
    vals.reserve( count );
    
    for( int i = 1; i <= count; i++ ) {
        vals.push_back( i );
    }

    cout << "computing sum1" << endl;
    unsigned long long sum1 = sum( vals );
    cout << "sum1 is " << sum1 << endl;

    cout << "computing sum2" << endl;
    unsigned long long sum2 = sum_dc( vals, 0, vals.size()-1 );

    cout << "sum2 is " << sum2 << endl;

    return 0;
}


