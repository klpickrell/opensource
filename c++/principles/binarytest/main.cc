#include <functional>
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    if( (1.0 - 1.0000000000000001) ) {
        cout << "raw - returns true" << endl;
    } else {
        cout << "raw - returns false" << endl;
    }

    if( 1.0 == 1.0000000000000001 ) {
        cout << "raw == returns true" << endl;
    } else {
        cout << "raw == returns false" << endl;
    }

    /*
    if( equal_to< double >()( 1.0, 1.0000000000000001 ) ) {
        cout << "equal_to returns true" << endl;
    } else {
        cout << "equal_to returns false" << endl;
    }
    */
  return 0;
}


