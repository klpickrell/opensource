#include <iostream>
#include <algorithm>

#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "boost/shared_ptr.hpp"

using namespace std;
/*
class variable
{
public:
    variable( const string& name,
              const string& value ) :
        _name( name ),
        _value( value ) {}

public:
    
    string name() const { return _name; }
    string value() const { return _value; }


private:

    string _name;
    string _value;
};
*/
template< typename T >
class predicate_caller
{
public:

    typedef boost::function< bool ( const T& ) > predicate;

public:
    predicate_caller( const T& value, predicate pred ) :
        _value( value ),
        _predicate( pred ) {}

    operator bool() const { return _predicate( _value ); }

private:

    T _value;
    predicate _predicate;
};

template< typename T >
class test
{
public:

    test( typename predicate_caller< T >::predicate pred ) :
        _predicate( pred ) {}


private:

    typename predicate_caller< T >::predicate _predicate;
};

class variable
{
public:
    ~variable(){}
    //    virtual void doit() { cout << "variable::doit" << endl; }
};

class integer_variable : public variable 
{
public:
    void doit() { cout << "integer_variable::doit" << endl; }

};
class string_variable : public variable 
{
public:
    void doit() { cout << "string_variable::doit" << endl; }
};


void dosomething( boost::shared_ptr< variable > ptr )
{
    ptr->doit();
}

int main( int argc, char** argv )
{

    //    using namespace boost::lambda;
    namespace bll = boost::lambda;
    bll::placeholder1_type arg1;
    bll::placeholder2_type arg2;
    bll::placeholder3_type arg3;

    dosomething( boost::shared_ptr< variable >( new integer_variable ) );
    dosomething( boost::shared_ptr< variable >( new string_variable ) );

    /*
    predicate_caller< string > p1( string( "hello" ), ( arg1 == "howdy" ) );
    if( p1 ) {
        cout << "p1 is true" << endl;
    } else {
        cout << "p1 is false" << endl;        
    }

    predicate_caller< double > p2( 2.14159, ( arg1 < 4 && arg1 > 3 ) );
    if( p2 ) {
        cout << "p2 is between 3 and 4" << endl;
    } else {
        cout << "p2 is NOT between 3 and 4" << endl;
    }
    */
    /*
    boost::shared_ptr< variable > v( new variable( "name1", "value1" ) );
    boost::shared_ptr< variable > v2( new variable( "name2", "value2" ) );

    predicate_caller< boost::shared_ptr< string > >::predicate p = ( *arg1 == "howdy" );
    if( p( boost::shared_ptr< string >( new string( "not howdy" ) ) ) ) {
        cout << "p( not howdy ) is true" << endl;
    } else {
        cout << "p( not howdy ) is false" << endl;
    }

    if( p( boost::shared_ptr< string >( new string( "howdy" ) ) ) ) {
        cout << "p( howdy ) is true" << endl;
    } else {
        cout << "p( howdy ) is false" << endl;
    }
    */
    //    boost::function< bool () > myfunc = boost::bind( std::equal_to< string >(), boost::bind( &variable::name, v ), "name1" );
    //    boost::function< bool () > myfunc = ( arg1 == "name1" );
    //    if( myfunc() ) {
    //        cout << "myfunc is true" << endl;
    //    } else {
    //        cout << "myfunc is false" << endl;
    //    }
    //    predicate_caller< boost::shared_ptr< variable > > p3( v, boost::bind( std::equal_to< string >(), boost::bind( &variable::name, v ), "name2" ) );
    //    if( p3 ) {
    //        cout << "p3 is true" << endl;
    //    } else {
    //        cout << "p3 is false" << endl;
    //    }



    /*
    (std::cout << boost::lambda::_1 << " " << boost::lambda::_2 << " " << boost::lambda::_3 << "\n")
        ("Hello","Lambda","World");

    boost::function< void(int,int,int) > f = 
        (std::cout << boost::lambda::_1 << "*" << 
         boost::lambda::_2 << "*" << boost::lambda::_3 << "=" << 
         boost::lambda::_1*boost::lambda::_2*boost::lambda::_3 << "\n");

        f( 1,2,3 );
        f(5,10,20);


    testme t;
    t.myval = "howdy";
    
    cout << boost::lambda::bind( &testme::myval, boost::lambda::_1 )( t ) << endl;

    vector< string > stuff;
    stuff.push_back( "thing1" );
    stuff.push_back( "thing2" );
    stuff.push_back( "thing3" );

    for_each( stuff.begin(), stuff.end(), (std::cout << boost::lambda::_1 << "\n") );
    */

    return 0;
}
