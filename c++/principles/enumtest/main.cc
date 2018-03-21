#include <iostream>
#include <map>
#include "boost/assign/list_of.hpp"
#include "boost/assert.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef enum {
        GPSEnum1,
        GPSEnum2
    }GPSEnum;

    std::map< GPSEnum,std::string> TextVal = boost::assign::map_list_of
        (GPSEnum1, "GPSEnum1")
        (GPSEnum2, "GPSEnum2");


    cout << "Converted text: " << TextVal[ GPSEnum1 ] << ", " << TextVal[ GPSEnum2 ] << endl;

    return 0;
}


