#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

#include <math.h>

using namespace std;

int main( int argc, char** argv )
{
    vector< float > vals;
    for( int i = 0; i < 10; i++ ) {

        //        vals.push_back( ((float)rand())/RAND_MAX );
        vals.push_back( static_cast< float >( i ) );
        vals.push_back( static_cast< float >( i ) );
    }

    sort( vals.begin(), vals.end() );

    //    float key = ((float)rand())/RAND_MAX;
    float key = 3.0;
    cout << "vector contents: ";
    copy( vals.begin(), vals.end(), ostream_iterator<float>( cout, "," ) );
    cout << endl;

    vector< float >::iterator lb = lower_bound( vals.begin(), vals.end(), key );
    cout << "lower_bound of " << key << " returns [index,value]: [" << lb - vals.begin() << "," << *lb << "]" << endl;

    lb = upper_bound( vals.begin(), vals.end(), key );
    cout << "upper_bound of " << key << " returns [index,value]: [" << lb - vals.begin() << "," << *lb << "]" << endl;

    key = 50;

    lb = lower_bound( vals.begin(), vals.end(), key );
    cout << "lower_bound of " << key << " returns [index,value]: [" << lb - vals.begin() << "," << *lb << "]" << endl;

    lb = upper_bound( vals.begin(), vals.end(), key );
    cout << "upper_bound of " << key << " returns [index,value]: [" << lb - vals.begin() << "," << *lb << "]" << endl;

    pair< vector< float >::iterator, vector< float >::iterator > rg = equal_range( vals.begin(), vals.end(), key );
    cout << "equal_range " << key << " returns [index,value], [index,value]: [" 
         << rg.first - vals.begin() << "," << *rg.first << "], [" << rg.second - vals.begin() << "," << *rg.second << "], " << endl;

    return 0;
}


