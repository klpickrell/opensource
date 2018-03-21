#include <iostream>

using namespace std;

class RefCounter
{
public:

    class rcounter {
    public:
        rcounter() { _count = 0; }
        int count() const { return _count; }

        void addref() { _count++; }
        void delref() { _count--; }
    };

    RefCounter() {
        _r = new rcounter;
    }
    
    RefCounter( const RefCounter& rhs ) {
        
    }
    
    ~RefCounter() {
        downcount();
    }

    int count() const { return _count; }

private:

    void upcount() { 
        _count++;
        cout << "RefCounter::upcount - " << _count << endl;
    }
    void downcount() { 
        _count--; 
        cout << "RefCounter::downcount - " << _count << endl;
    }


    int _count;
    rcounter* _r;
};


void something( RefCounter r ) {
    cout << "something was called" << endl;
}

int main( int argc, char** argv )
{
    cout << "Starting" << endl;

    RefCounter r;
    something( r );
    
    cout << "Exiting" << endl;
    return 0;
}


