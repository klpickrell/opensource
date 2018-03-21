#include <iostream>
#include <iomanip>

using namespace std;

struct other {
    
    unsigned int data;

};


struct x {
    unsigned char something_else;
    other* data;
};


int main( int argc, char** argv )
{
    x myx;
    myx.data = new other;

    cout << "x is " << hex << &myx << endl;
    cout << "x.data->data is " << hex << &myx.data->data << endl;
    cout << "x.data->data (parens) is " << hex << &(myx.data->data) << endl;

    delete myx.data;

    return 0;
}


