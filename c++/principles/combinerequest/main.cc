#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_dynamic.hpp>
#include <boost/bind.hpp>
#include <boost/function_output_iterator.hpp>

#include "CombineRequest.h"

using namespace std;
using namespace boost::spirit::classic;

ostream& operator<<( ostream& lhs, const GeoID& rhs )
{
    lhs << "GeoID productID=" << rhs.productID();
    return lhs;
}

int main( int, char** )
{
    string geo( "{"
                "geoID { productID1, activityID1, actionID1, 1 }"
                "geoID { productID2, activityID2, actionID2, 2 }"
                "geoID { productID3, activityID3, actionID3, 3 }"
                "geoID { productID4, activityID4, actionID4, 4 }"
                "}" );

    string geo2( "{"
                "geoID{productID1,activityID1,actionID1,1}"
                "geoID{productID2,activityID2,actionID2,2}"
                "geoID{productID3,activityID3,actionID3,3}"
                "geoID{productID4,activityID4,actionID4,4}"
                "}" );

    string geo3( "{geoID{ngate100_2010-04-20T13:53:09.395Z,ndrt2155_2010-04-20T13:52:12.566Z,ndrt2155_2010-04-20T13:53:01.582Z,1}"
                 "geoID{ngate100_2010-04-20T13:53:08.334Z,ndrt2155_2010-04-20T13:52:12.566Z,ndrt2155_2010-04-20T13:53:01.579Z,1}"
                 "geoID{ngate100_2010-04-20T13:53:08.333Z,ndrt2155_2010-04-20T13:52:12.566Z,ndrt2155_2010-04-20T13:53:01.579Z,0}"
                 "geoID{ngate100_2010-04-20T13:53:09.394Z,ndrt2155_2010-04-20T13:52:12.566Z,ndrt2155_2010-04-20T13:53:01.582Z,0}"
                 "}" );

    vector<string> productID;
    vector<string> activityID;
    vector<string> actionID;
    vector<int> index;

    try {
        CombineRequest request( "invalid snl;", 
                                geo3 );

        vector<GeoID> geos = request.getGeos();
        cout << "got " << geos.size() << " geos: " << endl;
        copy( geos.begin(), geos.end(), ostream_iterator<GeoID>(cout, "\n") );
        cout << endl;

//        for_each( geos.begin(), geos.end(),
//                  boost::bind( &vector<string>::push_back, productID, boost::bind<string>( &GeoID::productID, _1 ) ) );

        transform( geos.begin(), geos.end(), std::back_inserter(productID), boost::bind( &GeoID::productID, _1 ) );

    } catch( const combine_parse_error& ex ) {
        cerr << ex.what() << endl;
        return 1;
    }


    cout << "productIDs: ";
    copy( productID.begin(), productID.end(), ostream_iterator<string>(cout, " ") );
    cout << endl;

/*
    cout << "activityIDs: ";
    copy( activityID.begin(), activityID.end(), ostream_iterator<string>(cout, " ") );
    cout << endl;

    cout << "actionIDs: ";
    copy( actionID.begin(), actionID.end(), ostream_iterator<string>(cout, " ") );
    cout << endl;

    cout << "indices: ";
    copy( index.begin(), index.end(), ostream_iterator<int>(cout, " ") );
    cout << endl;
*/

    return 0;
}
