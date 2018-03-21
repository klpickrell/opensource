#include <iostream>
using namespace std;


class base
{
public:
    ~base() { cout << "base::~base" << endl; }

    void dosomething() const { cout << "base::dosomething" << endl; }
};

class derived : public base
{
public:
    ~derived() { cout << "derived::~derived" << endl; }

    void dosomething() const { cout << "derived::dosomething" << endl; }
};


int main( int argc, char** argv )
{
    const base& b = derived();
    b.dosomething();
}
