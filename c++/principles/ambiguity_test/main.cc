#include <iostream>

using namespace std;

class A {
public:
    A() { cout << "A::A" << endl; }
};

int main( int argc, char** argv )
{
    A a();

    A b;

    return 0;
}


