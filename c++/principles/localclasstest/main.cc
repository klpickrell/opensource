#include <iostream>
#include <vector>

using namespace std;

template< class T >
class mytemplate
{
 public:
    mytemplate( const T& t ) :
        _t( t ) {}


public:
    void operator()() {
        _t();
    }

 private:
    
    T _t;
};

void doit()
{
    class LocalDoit
    {
    public:
        void operator()(){
            cout << "LocalDoit" << endl;
        }
    };


    //    LocalDoit a;
    //    a();

    mytemplate< LocalDoit > _mydoits( LocalDoit() );

    _mydoits();

}


int main( int argc, char** argv )
{
    cout << "calling doit" << endl;
    doit();
    return 0;
}


