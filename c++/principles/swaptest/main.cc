#include <iostream>
#include <iomanip>

using namespace std;

template< typename T >
void swapinplace( T& thet )
{
    for( int i = 0; i < (int)(sizeof(T)/2); i++ ) {
        
        char* tbytes = (char*)&thet;

        tbytes[ i ] ^= tbytes[ sizeof(T)-i -1 ];
        tbytes[ sizeof(T)-i - 1 ] ^= tbytes[ i ];
        tbytes[ i ] ^= tbytes[ sizeof(T)-i -1 ];
    }
}

int main( int argc, char** argv )
{
    int a = 0x12345678;
    cout << "swapping integer: " << hex << a << endl;

    swapinplace( a );

    cout << "swapped: " << hex << a << endl;

    return 0;
}


