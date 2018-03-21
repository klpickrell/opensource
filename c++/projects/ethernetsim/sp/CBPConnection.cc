#include <iostream>

#include "CBPConnection.h"
#include "FrameBuilder.h"
#include "Select.h"

#include "boost/bind.hpp"

using namespace std;

CBPConnection::CBPConnection( const Socket& sock, const std::string& name ) :
    socket( sock ),
    _name( name ),
    reader( sock ),
    writer( sock )
{
    reader.output.connect( boost::bind( &CBPConnection::onFrameSlot,
                                        this,
                                        _1 ) );

    reader.socket_closed.connect( boost::bind( &CBPConnection::onCloseSlot,
                                               this,
                                               _1 ) );

    reader.socket_exception.connect( boost::bind( &CBPConnection::onExceptionSlot,
                                                  this,
                                                  _1, _2 ) );

    writer.socket_closed.connect( boost::bind( &CBPConnection::onCloseSlot,
                                               this,
                                               _1 ) );

    writer.socket_exception.connect( boost::bind( &CBPConnection::onExceptionSlot,
                                                  this,
                                                  _1, _2 ) );

    SelectManager::instance()->add( socket.sock(),
                                    SelectManager::Readable,
                                    boost::bind( &FrameReader::onReadableSlot,
                                                 &reader,
                                                 _1 ) );

    SelectManager::instance()->add( socket.sock(),
                                    SelectManager::Writeable,
                                    boost::bind( &CBPConnection::onWriteableSlot,
                                                 this,
                                                 _1 ) );
}

void CBPConnection::sendInitMsg()
{
    Ethernet::Frame frame = Ethernet::FrameBuilder::build( 1,1,1,
                                                           name(),
                                                           "cbp",
                                                           string( "initsp name=" ) + name() );
    writer.write( frame );
}

void CBPConnection::onFrameSlot( const Ethernet::Frame& frame )
{
    cout << "SP CBPConnection received frame: " << frame << endl;
    vector<char> data = frame.data();
    std::copy( data.begin(), data.end(),
               back_inserter( input_frame_buffer ) );

    if( frame.sequence_num() == frame.total_frames() ) {
        boost::shared_ptr<char> sdata( strndup( reinterpret_cast<char*>(&data[0]),
                                                data.size() ),
                                       free );
        if( sdata ) {
            cout << "received " << sdata.get() << endl;
            input_frame_buffer.clear();
        }
    }
}
