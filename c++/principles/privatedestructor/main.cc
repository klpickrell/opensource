#include <iostream>

using namespace std;

class Honky
{
public:
    void tonk() const { cout << "Honky::tonk" << endl; }

private:
    ~Honky() { cout << "Honky::~Honky" << endl; }
};

int main( int argc, char** argv )
{
    // Honky h; // fails to compile

    Honky* h = new Honky;
    h->tonk();

    //    delete h; // fails to compile
    
    return 0;
}


