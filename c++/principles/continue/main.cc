#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    cout << "Starting while loop..." << endl;
    int count = 0;
    while( count < 3 ) {
        cout << "count is " << count << endl;
        for( int i = 0; i < 2; i++ ) {
            cout << "inside for loop, i is " << i << endl;
            goto thewhile;
        }

        count++;
    }


  return 0;
}


