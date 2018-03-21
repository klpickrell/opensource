#include "singleton.h"
#include <iostream>
#include "boost/shared_ptr.hpp"

using namespace std;
using namespace Tg;
using namespace boost;


class siggen
{
public:
    siggen() { cout << "siggen::siggen" << endl; }
    ~siggen() { cout << "siggen::~siggen" << endl; }

    void arm() const { cout << "siggen::arm" << endl; }
};

class onlyone : public singleton< onlyone >
{
     DECLARE_SINGLETON_FRIENDS( onlyone );
    /*
private:
    onlyone() :
        _siggen( new siggen ) 
    { 
        cout << "onlyone::onlyone" << endl; 
    }
    */

    ~onlyone() { cout << "onlyone::~onlyone" << endl; }

public:

    shared_ptr< siggen > getsiggen() { return _siggen; }

private:
    
    shared_ptr< siggen > _siggen;
};


int main( int argc, char** argv )
{
    cout << "calling onlyone::instance()->getsiggen()->arm()" << endl;
    onlyone::instance()->getsiggen()->arm();

    onlyone o;
    o.getsiggen()->arm();

    cout << "final statement" << endl;
    return 0;
}


