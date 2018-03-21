#include <iostream>

using namespace std;

class Abstract
{
public:
    virtual ~Abstract(){}

public:
    virtual void doit() = 0;
};

class Derived : public Abstract
{
public:

    ~Derived() { cout << "Derived::~Derived" << endl; }

public:
    
    void doit() { cout << "Derived::doit" << endl; }
};

int main( int argc, char** argv )
{
    Abstract* abs = new Derived;
    abs->doit();
    delete abs;

    return 0;
}


