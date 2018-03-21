#include <algorithm>
#include <iterator>
#include <sstream>

#include "FrameBuilder.h"

#include "FrameScript.h"

using namespace std;

FrameScript::FrameScript( const std::string& filename ) throw( FileException, Ethernet::FormatError )
    try 
    : file( filename.c_str(), ios::in )
{
    vector<string> lines;
    string line;
    while (std::getline(file, line)) {
        lines.push_back( line );
    }

    string pass;
    unsigned int frame_id;
    unsigned int part;
    unsigned int total;
    string to;
    string from;
    for( vector<string>::iterator it = lines.begin();
         it != lines.end();
         ++it ) {

        if( it->length() < 10 ) {
            continue;
        }

        istringstream is(*it);
        is >> pass 
           >> frame_id >> pass 
           >> part >> pass 
           >> total >> pass 
           >> to >> pass 
           >> from;

        frames.push_back( Ethernet::FrameBuilder::build( part, total,
                                                         frame_id,
                                                         from,
                                                         to,
                                                         "test frame" ) );
    }

} catch( const std::exception& ex ) {
    throw FileException( std::string( "exception on FrameScript construction: " ) + ex.what() );
}
