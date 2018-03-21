#ifndef FRAME_WRITER__H
#define FRAME_WRITER__H

#include "EthernetFrame.h"
#include "Socket.h"
#include "boost/signals.hpp"

#include <vector>

class FrameWriter
{
public:
    FrameWriter( const Socket& sock ) :
        socket( sock )
    {}

    void write( const Ethernet::Frame& frame );
    void flush();

    void clear_buffers() { frame_buffer.clear(); }

    int bytes_remaining() const { return frame_buffer.size(); }

    boost::signal<void( const Socket& sock )> socket_closed;
    boost::signal<void( const Socket& sock, int )> socket_exception;


/*
public slots:
*/
      
    void onWriteableSlot( int sock ) {
        if( socket.sock() == sock ) {
            flush();
        }
    }
    
private:

    Socket socket;
    std::vector<char> frame_buffer;
};

#endif
