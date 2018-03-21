#include <iostream>

using namespace std;

template< typename T1, typename T2 >
class SpunkyOne
{
public:
    SpunkyOne( T1 t1, T2 t2 ) { _t1 = t1; _t2 = t2; cout << "Very Generic SpunkyOne: " << _t1 << ", " << _t2 << endl; }

private:
    T1 _t1;
    T2 _t2;
};

template< typename T1, typename T2 >
class SpunkyOne< T1*, T2* >
{
public:
    SpunkyOne( T1* t1, T2* t2 ) { _t1 = t1; _t2 = t2; cout << "Generic Pointer SpunkyOne: " << _t1 << ", " << _t2 << endl; }

private:
    T1* _t1;
    T2* _t2;
};

template< typename T1 >
class SpunkyOne< T1*, T1* >
{
public:
    SpunkyOne( T1* t1 ) { _t1 = t1; cout << "Same Pointer SpunkyOne: " << _t1 << ", " << endl; }

private:
    T1* _t1;
};

template< typename T2 >
class SpunkyOne< int, T2 >
{
public:
    SpunkyOne( int i ) { _i = i; cout << "Specialized int, T SpunkyOne: " << i << endl; }
    //    SpunkyOne() { _t = T; }

    //    void printit() { cout << "Mostly Generic SpunkyOne: " << _t << endl; }

private:

    int _i;
};

template<>
class SpunkyOne< int, int >
{
public:
    SpunkyOne( int i ) { _i = i; cout << "Specialized int, int SpunkyOne:" << i << endl; }
    //    SpunkyOne() { _t = T; }

    //    void printit() { cout << "Mostly Generic SpunkyOne: " << _t << endl; }

private:

    int _i;
};

template< typename T1 >
class SpunkyOne< T1, int >
{
public:
    SpunkyOne( int i ) { _i = i; cout << "Specialized T, int SpunkyOne:" << i << endl; }
    //    SpunkyOne() { _t = T; }

    //    void printit() { cout << "Mostly Generic SpunkyOne: " << _t << endl; }

private:

    int _i;
};

/*
template<>
class SpunkyOne<>
{
public:
    SpunkyOne() { _i = 0; cout << "Extra Special SpunkyOne: " << _i << endl; }

private:

    int _i;
};
*/

int main( int argc, char** argv )
{
    //    cout << "Creating very generic SpunkyOne" << endl;
    //    SpunkyOne<string> d( "howdy" );
    SpunkyOne z1( 2 );
    SpunkyOne<int, int > z2( 3 );
    SpunkyOne< double, int > z3( 5 );
    SpunkyOne<double, double> z4( 2.0, 4.0 );

    double blah = 2.0;
    int blah2 = 1;
    SpunkyOne<double*, double*> z5( &blah );
    SpunkyOne<int*,double*> z6( &blah2, &blah );


    return 0;
}


