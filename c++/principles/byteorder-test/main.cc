#include <iostream>
#include <iomanip>

#include "byteswap.h"

using namespace std;

int main( int argc, char** argv )
{

    unsigned int a = 0x12345678;
    unsigned short b = 0x1234;

    cout << "a: " << hex << a << " swapped: " << hex << byteswap( a ) << endl;
    cout << "b: " << hex << b << " swapped: " << hex << byteswap( b ) << endl;

    return 0;
}


