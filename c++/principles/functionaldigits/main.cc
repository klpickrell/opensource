#include <iostream>

using namespace std;

int numdigits( int x )
{
    if( x < 10 ) {
        return 1;
    } else {
        return numdigits( x/10 ) + 1;
    }
}


int main( int argc, char** argv )
{
    int nd;
    cout << "enter number: ";
    cin >> nd;

    cout << "number of digits in " << nd << " is " << numdigits( nd ) << endl;
    return 0;
}


