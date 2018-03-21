#include "CombineRequest.h"

#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/iterator/zip_iterator.hpp>

#include <boost/bind.hpp>

using namespace std;

CombineRequest::CombineRequest( const string& text,
                                const string& geos ) throw( combine_parse_error ) :
    m_text( text )
{
    using namespace boost::spirit::classic;

    vector<string> productID;
    vector<string> activityID;
    vector<string> actionID;
    vector<int> index;

    if( !parse( geos.c_str(),
                ch_p('{') >> *(str_p( "geoID" ) 
                               >> ch_p('{')
                               >> (*( print_p - ch_p(',') ))[ push_back_a( productID ) ] >> ch_p(',')
                               >> (*( print_p - ch_p(',') ))[ push_back_a( activityID ) ] >> ch_p(',')
                               >> (*( print_p - ch_p(',') ))[ push_back_a( actionID ) ] >> ch_p(',')
                               >> uint_p[ push_back_a( index ) ] 
                               >> ch_p('}')) 
                >> ch_p('}'), space_p ).full ) {

        throw combine_parse_error( string("parse failed in CombineRequest on ") + geos );
    }

    std::for_each( boost::make_zip_iterator( boost::make_tuple( productID.begin(),
                                                                activityID.begin(),
                                                                actionID.begin(),
                                                                index.begin() ) ),
                   boost::make_zip_iterator( boost::make_tuple( productID.end(),
                                                                activityID.end(),
                                                                actionID.end(),
                                                                index.end() ) ),
                   boost::bind( &CombineRequest::addCombine, this, _1 ) );
}
