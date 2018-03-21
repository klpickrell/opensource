#include <iostream>

using namespace std;

class InlineTester
{
public:
    
    inline void doit_twice() { doit_once(); }
    inline void doit_once() 
    { 
        asm(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            );
    }

};

int main( int argc, char** argv )
{
    InlineTester t;

        asm (
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            );

    t.doit_twice();

        asm (
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            );

    return 0;
}


