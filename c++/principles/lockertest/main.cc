#include <iostream>
#include <iomanip>

using namespace std;

int main( int argc, char** argv )
{
    char* key;                  // Make an unnumbered key containing uninitialized garbage.
    key = (char*)malloc(10);    // Ask the attendant for the number of a locker big enough to store 10 chars (10 bytes)
                                // malloc means "memory allocate"
    if( !key ) {
        cerr << "We Couldn't get a number for our key :(\n";
    } else {
        cout << "We got a key!  Our key is now assigned to locker " << showbase << hex << (unsigned long)key << "\n";
        free( key );            // Give the key back to the attendant
    }


    // Now, using 'key' in any way is a big no-no because it's not assigned to a locker.

    key = 0;          // 

    return 0;
}
