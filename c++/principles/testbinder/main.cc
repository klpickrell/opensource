#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

class Organism
{
public:
    Organism( int val ) : _value( val ){}

    int value() const { return _value; }

    void print() const { cout << "Organism!: " << _value << endl; }

private:

    int _value;
};

class OrganismComparator
{
public:
    OrganismComparator( int val ) : _value( val ) {}

    bool operator()( const Organism& org ) const {
        return (org.value() == value());
    }

    int value() const { return _value; }

private:

    int _value;
};

int main( int argc, char** argv )
{
    vector< Organism > orgs;
    for( int i = 0; i < 10; i++ ) {
        orgs.push_back( Organism( i ) );
    }
    /*
    greater< int > a;
    bool b = a( 5, 2 );
    cout << (b?"true":"false") << endl;

    b = a( 2, 5 );
    cout << (b?"true":"false") << endl;

    b = a( 2, 2 );
    cout << (b?"true":"false") << endl;

    multiplies< int > mul;
    cout << mul( 5, 2 ) << endl;
    */
    vector< Organism >::iterator pos = find_if( orgs.begin(),
                                                orgs.end(),
                                                OrganismComparator( 5 ) );

    if( pos != orgs.end() ) {
        cout << "Organism found" << endl;
        pos->print();
    } else {
        cout << "No Organism found" << endl;
    }

    return 0;
}


