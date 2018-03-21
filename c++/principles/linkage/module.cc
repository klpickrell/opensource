#include <iostream>

using namespace std;

extern int i;

void print_something()
{
    i = 10;
    cout << "something" << endl;
}

