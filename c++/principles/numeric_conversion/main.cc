#include <iostream>
#include <sstream>

using namespace std;

struct mything
{
    int a;
    int b;
    double c;
    char d[0];
};

int main( int argc, char** argv )
{
    string s = "20SBTProcessor.uff";
    istringstream is;
    is.str( s );
    unsigned int i;
    string name;
    is >> i >> name;
    cout << name << "\n";

    cout << "sizeof(mything) is " << sizeof(mything) << "\n";

    return 0;
}
