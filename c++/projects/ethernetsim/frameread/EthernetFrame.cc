#include <errno.h>
#include <ostream>

#include <arpa/inet.h>

#include "EthernetFrame.h"

#include "boost/shared_ptr.hpp"

using namespace Ethernet;
using namespace std;

Frame::Frame( const vector<char>& frame, int bo ) throw( FormatError ) :
    byte_order( bo )
{
    setBuffer( frame );
}

Frame::Frame( const char* source, int length, int bo ) throw( FormatError ) :
    byte_order( bo )
{
    setBuffer( source, length );
}

void Frame::setBuffer( const char* source, int length ) throw( FormatError )
{
    if( !source || length < FRAME_HEADER_LENGTH ) {
        throw FormatError( "Frame::setBuffer cannot create Frame instance with invalid contents" );
    }

    const char* cursor = source;

    boost::shared_ptr<char> sync( strndup( cursor, SYNC_SIZE ),
                                  free );

    if( !sync ) {
        throw FormatError( string( "strndup error: " ) + strerror(errno) );
    }

    if( !(string( sync.get() ) == sync_string) ) {
        throw FormatError( "Frame::setBuffer: didnt find sync_string at start of frame" );
    }

    _data.resize( length );
    memcpy( &_data[0], source, length );
}

unsigned int Frame::data_length() const
{
    Header* header = reinterpret_cast<Header*>( const_cast<char*>(&_data[0]) );
    if( byte_order == BYTE_ORDER_NETWORK ) {
        return ntohl( header->data_length );
    } else {
        return header->data_length;
    }
}

unsigned int Frame::sequence_num() const
{
    Header* header = reinterpret_cast<Header*>( const_cast<char*>(&_data[0]) );
    if( byte_order == BYTE_ORDER_NETWORK ) {
        return ntohl( header->sequence_num );
    } else {
        return header->sequence_num;
    }
}

unsigned int Frame::total_frames() const
{
    Header* header = reinterpret_cast<Header*>( const_cast<char*>(&_data[0]) );
    if( byte_order == BYTE_ORDER_NETWORK ) {
        return ntohl( header->total_frames );
    } else {
        return header->total_frames;
    }
}

unsigned int Frame::frame_id() const
{
    Header* header = reinterpret_cast<Header*>( const_cast<char*>(&_data[0]) );
    if( byte_order == BYTE_ORDER_NETWORK ) {
        return ntohl( header->frame_id );
    } else {
        return header->frame_id;
    }
}

string Frame::to() const
{
    char buf[16];
    Header* header = reinterpret_cast<Header*>( const_cast<char*>(&_data[0]) );
    strncpy( buf, header->to, sizeof(buf) );
    buf[15] = 0;
    return string( buf );
}

string Frame::from() const
{
    char buf[16];
    Header* header = reinterpret_cast<Header*>( const_cast<char*>(&_data[0]) );
    strncpy( buf, header->from, sizeof(buf) );
    buf[15] = 0;
    return string( buf );
}

vector<char> Frame::data() const
{
    return vector<char>( _data.begin() + FRAME_HEADER_LENGTH,
                         _data.begin() + (FRAME_HEADER_LENGTH+data_length()) );
}

ostream& operator<<( ostream& lhs, const Ethernet::Frame& frame )
{
    vector<char> frame_data = frame.data();
    boost::shared_ptr<char> data( strndup( reinterpret_cast<char*>( const_cast<char*>(&(frame_data)[0])),
                                           frame_data.size()),
                                  free );

    lhs << "Header { frame_id=" << frame.frame_id() 
        << " sequence_num=" << frame.sequence_num()
        << " total_frames=" << frame.total_frames()
        << " from=" << frame.from()
        << " to=" << frame.to()
        << " data_length=" << frame.data_length() << " } "
        << "Data { " << data.get() << " }";

    return lhs;
}


