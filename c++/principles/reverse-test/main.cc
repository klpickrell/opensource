#include <iostream>
#include <algorithm>

using namespace std;

int main( int argc, char** argv )
{

    string reverse_me( "Hello World!" );
    
    cout << "pre-reversal: " << reverse_me << endl;

    reverse( reverse_me.begin(), reverse_me.end() );

    cout << "post-reversal: " << reverse_me << endl;

    return 0;
}


