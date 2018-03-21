#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/info_parser.hpp>

using namespace std;

namespace pt = boost::property_tree;
using pt::ptree;

typedef pt::basic_ptree<string, boost::any> my_ptree;

int main( int /*argc*/, char** /*argv*/ )
{
    ptree tree;

    try {
        ifstream file( "xmlfile.xml" );
        pt::read_xml( file, tree );
    } catch( pt::xml_parser_error& ex ) {
        cout << ex.message() << endl;
        return 1;
    }

    tree.put( "thing.gizmovalue", 5.2 );
    tree.put( "item.gizmovalue", 5.2 );
    tree.get_child( "thing" ).put( "thing2.gizmovalue2", 10.4 );
    tree.get_child( "thing2.gizmovalue2" ).put( "thing3.gizmo", 1 );

    cout << "===info===" << endl;
    write_info( cout, tree );
    cout << "===xml===" << endl;
    write_xml( cout, tree );
    cout << "\n";

    return 0;
}
