#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    cout << "Hello World!\n";

    int a[5];
    cout << "sizeof(a): " << sizeof( a ) << endl;
    cout << "sizeof(&a[0]): " << sizeof( &a[0] ) << endl;
    cout << "sizeof((int*)a): " << sizeof( (int*)a ) << endl;

    cout << "16/32=" << 16/32 << endl;
    cout << "32/32=" << 32/32 << endl;
    cout << "33/32=" << 33/32 << endl;

    return 0;
}
