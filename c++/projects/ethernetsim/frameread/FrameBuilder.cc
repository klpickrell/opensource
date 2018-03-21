#include "FrameBuilder.h"
#include "NetworkHeader.h"

#include <vector>

using namespace std;
using namespace Ethernet;

Frame FrameBuilder::build( unsigned int seq,
                           unsigned int total,
                           unsigned int frame_id,
                           const std::string& from,
                           const std::string& to,
                           const std::string& data )
{
    NetworkHeader nheader( seq,total,
                           frame_id,
                           from,
                           to,
                           data.length() );

    vector<char> frame_buffer;
    Ethernet::Header header = nheader;
    std::copy( reinterpret_cast<char*>(&header), 
               reinterpret_cast<char*>(&header) + sizeof(header),
               back_inserter( frame_buffer ) );
    
    std::copy( data.begin(), data.end(),
               back_inserter( frame_buffer ) );

    return Ethernet::Frame( frame_buffer, BYTE_ORDER_NETWORK );
}

Frame FrameBuilder::build( unsigned int seq,
                           unsigned int total,
                           unsigned int frame_id,
                           const std::string& from,
                           const std::string& to,
                           const std::vector<char> data )
{
    NetworkHeader nheader( seq,total,
                           frame_id,
                           from,
                           to,
                           data.size() );

    vector<char> frame_buffer;
    Ethernet::Header header = nheader;
    std::copy( reinterpret_cast<char*>(&header), 
               reinterpret_cast<char*>(&header) + sizeof(header),
               back_inserter( frame_buffer ) );
    
    std::copy( data.begin(), data.end(),
               back_inserter( frame_buffer ) );

    return Ethernet::Frame( frame_buffer, BYTE_ORDER_NETWORK );
}
