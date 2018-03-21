#include <iostream>
#include <vector>
#include <iterator>
#include <exception>
#include <algorithm>
#include <set>

#include <boost/random.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>

using namespace std;

int secondLargest1( const vector<int>& input ) throw( std::runtime_error )
{
    if( input.empty() ) {
        throw std::runtime_error( "descriptive error message" );
    }

    int max = input[0];
    int notmax = max;

    {
        using namespace boost::lambda;

        // using Joel de Guzmann's improved syntax for boost lambda

        std::for_each( input.begin(),
                       input.end(),
                       ( if_( _1 > var(max) ) [ 
                          var(notmax) = max, 
                          var(max) = _1 
                         ] .
                         else_ [
                           if_( _1 > var(notmax) ) [ 
                             if_( _1 < var(max) ) [ 
                               var(notmax) = _1 
                             ] 
                           ] 
                         ] ) 
                       );
    }

    return notmax;
}

int secondLargest2( const vector<int>& input ) throw( std::runtime_error )
{
    if( input.empty() ) {
        throw std::runtime_error( "descriptive error message" );
    }

    vector<int> acopy( input );
    std::sort( acopy.begin(), acopy.end() );
    vector<int>::iterator pivot = std::lower_bound( acopy.begin(), acopy.end(), acopy[ acopy.size() -1 ] );
    if( pivot != acopy.begin() ) {
        --pivot;
    }
    
    return *pivot;
}

int secondLargest3( const vector<int>& input ) throw( std::runtime_error )
{
    if( input.empty() ) {
        throw std::runtime_error( "descriptive error message" );
    }

    set<int> resultset( input.begin(), input.end() );

    if( resultset.size() == 1 ) {
        return *resultset.begin();
    } else {
        return *(++resultset.rbegin());
    }
}

int main( int argc, char** argv )
{
    const int maxelements = 40;

    boost::mt19937 rng;
    boost::uniform_int<> therange( 1, maxelements );

    boost::variate_generator< boost::mt19937&, boost::uniform_int<> > dice( rng, therange );

    vector<int> vec( maxelements );
    generate( vec.begin(), vec.end(), dice );

    /*
      // or if you want a vector of uniform values
      
      generate(vec.begin(), vec.end(), boost::lambda::constant( 10 ) );

    */

    /* 
       // or if rand is sufficient

    vector<int> vec( maxelements );
    generate_n( back_inserter( vec ), max_elements, rand );

    */

    cout << "input vector: ";
    copy( vec.begin(), vec.end(), ostream_iterator<int>( cout, " " ) );
    cout << endl;

    cout << "max is: " << *(std::max_element( vec.begin(), vec.end() )) << endl;
    cout << "secondLargest1 (linear): " << secondLargest1( vec ) << endl;
    cout << "secondLargest2 (logilinear): " << secondLargest2( vec ) << endl;
    cout << "secondLargest3:(lg(n!) = also logilinear " << secondLargest3( vec ) << endl;

    return 0;
}


