#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_dynamic.hpp>
//#include <boost/spirit/include/classic_core.hpp>

using namespace std;
using namespace boost::spirit::classic;

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

    if( parse( geo.c_str(),
               ch_p('{') >> *(str_p( "geoID" ) >> ch_p('{')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( productID ) ] >> ch_p(',')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( activityID ) ] >> ch_p(',')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( actionID ) ] >> ch_p(',')
                                      >> uint_p[ push_back_a( index ) ] 
                                      >> ch_p('}')) >> ch_p('}'), space_p ).full ) {

        cout << "geo parsing success" << endl;
    } else {
        cout << "geo parsing failure" << endl;
    }

    if( parse( geo2.c_str(),
               ch_p('{') >> *(str_p( "geoID" ) >> ch_p('{')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( productID ) ] >> ch_p(',')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( activityID ) ] >> ch_p(',')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( actionID ) ] >> ch_p(',')
                                      >> uint_p[ push_back_a( index ) ] 
                                      >> ch_p('}')) >> ch_p('}'), space_p ).full ) {

        cout << "geo2 parsing success" << endl;
    } else {
        cout << "geo2 parsing failure" << endl;
    }

    if( parse( geo3.c_str(),
               ch_p('{') >> *(str_p( "geoID" ) >> ch_p('{')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( productID ) ] >> ch_p(',')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( activityID ) ] >> ch_p(',')
                                      >> (*( print_p - ch_p(',') ))[ push_back_a( actionID ) ] >> ch_p(',')
                                      >> uint_p[ push_back_a( index ) ] 
                                      >> ch_p('}')) >> ch_p('}'), space_p ).full ) {

        cout << "geo3 parsing success" << endl;
    } else {
        cout << "geo3 parsing failure" << endl;
    }


    cout << "productIDs: ";
    copy( productID.begin(), productID.end(), ostream_iterator<string>(cout, " ") );
    cout << endl;

    cout << "activityIDs: ";
    copy( activityID.begin(), activityID.end(), ostream_iterator<string>(cout, " ") );
    cout << endl;

    cout << "actionIDs: ";
    copy( actionID.begin(), actionID.end(), ostream_iterator<string>(cout, " ") );
    cout << endl;

    cout << "indices: ";
    copy( index.begin(), index.end(), ostream_iterator<int>(cout, " ") );
    cout << endl;


    return 0;
}
