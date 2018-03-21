#include "boost/signal.hpp"
#include "boost/bind.hpp"

#include <iostream>

using namespace std;

class Thing
{
public:
    Thing( int i, int j ) :
        i(i),
        j(j){}

    explicit Thing( int i ) :
        i(i){}

    int i;
    int j;
};

float sum_slot( float a, float b )
{
    cout << "computing sum of " << a << " and " << b << endl;
    return a+b;
}

float product_slot( float a, float b )
{
    cout << "computing product of " << a << " and " << b << endl;
    return a*b;
}

float difference_slot( float a, float b )
{
    cout << "computing difference of " << a << " and " << b << endl;
    return a-b;
}

template< typename T >
struct maximum
{
    typedef T result_type;

    template< typename InputIterator >
    result_type operator()( InputIterator first, InputIterator last ) const
    {
        cout << "maximum::operator() called" << endl;
        if( first == last ) {
            return result_type();
        }

        result_type r = *first++;

        while( first != last ) {

            if( r < *first ) {
                r = *first;
            }

            ++first;
        }

        return r;
    }

};


class Slot : public boost::signals::trackable
{
public:

    explicit Slot( int val ) :
        val( val )
    {
        cout << "Slot" << val << " enters the world" << endl;
    }

    Slot( const Slot& slot ) :
        val( slot.val )
    {
        cout << "Slot" << val << " enters the world via copy" << endl;
    }

    ~Slot() {
        cout << "Slot" << val << " go bye-bye" << endl;
    }

    void slotcall( const std::string& prefix ) const 
    {
        cout << "Slot::slotcall --> " << prefix << val << endl;
    }

    void operator()( const std::string& prefix ) const
    {
        return slotcall( prefix );
    }

private:

    int val;
};



int main( int argc, char** argv )
{
    /*
    boost::signal< float (float,float), maximum< float > > float_sigs;

    float_sigs.connect( &sum_slot );
    float_sigs.connect( &product_slot );
    float_sigs.connect( &difference_slot );

    float_sigs( 5, 3 );


    Thing thing( 1, 2 );
    Thing thing2( thing );

    cout << "thing2: " << thing2.i << "," << thing2.j << endl;
    */

    boost::signal< void( const string& ) > sig;
    
    Slot* slot1 = new Slot( 1 );
    Slot* slot2 = new Slot( 2 );
    Slot* slot3 = new Slot( 3 );

    /*
    sig.connect( boost::bind( &Slot::slotcall,
                              slot1,
                              _1 ) );

    sig.connect( boost::bind( &Slot::slotcall,
                              slot2,
                              _1 ) );

    sig.connect( boost::bind( &Slot::slotcall,
                              slot3,
                              _1 ) );
    */

    boost::shared_ptr<Slot> slot( new Slot( 5 ) );
    sig.connect( *slot );

    sig( "howdy" );
    sig( "another howdy" );

    delete slot1;
    delete slot2;
    delete slot3;

    sig( "crash" );
    
    return 0;
}


