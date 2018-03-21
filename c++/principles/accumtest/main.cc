#include <algorithm>
#include <numeric>

#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    int vals[] = { 1,2,3,4,5 }; // sum is 15
    cout << "sum is " << accumulate( vals, vals+5, 0 ) << endl;
    cout << "product is " << accumulate( vals, vals+5, 1, multiplies<int>() ) << endl;
    return 0;
}


