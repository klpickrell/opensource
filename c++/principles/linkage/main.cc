#include <iostream>

using namespace std;

int i;
void print_something();

int main( int argc, char** argv )
{
    i = 5;
    cout << "main... i is " << i << endl;
    print_something();
    cout << "main... i is " << i << endl;
}


