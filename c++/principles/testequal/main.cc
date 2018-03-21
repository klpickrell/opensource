#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    int a[4] = { 1, 2, 3, 4 };
    int b[4] = { 1, 2, 3, 4 };

    int c = a;

    
    if( a == b ) {
        cout << "equal" << endl;
    } else {
        cout << "not equal" << endl;
    }

  return 0;
}


