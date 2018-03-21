#include <iostream>

using namespace std;

struct MyStruct {
    
    int value1;
    int value2;
    char value3[4];

};

int main( int argc, char** argv )
{
    cout << "sizeof MyStruct: " 
         << sizeof( MyStruct ) 
         << ", sizeof MyStruct::value1: " 
         << sizeof( MyStruct::value1 ) << endl;
        

    return 0;
}


