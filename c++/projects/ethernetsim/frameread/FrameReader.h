#ifndef FRAME_READER__H
#define FRAME_READER__H

#include "EthernetFrame.h"
#include "Socket.h"
#include "boost/signals.hpp"

#include <vector>

class FrameReader
{
public:
    FrameReader( const Socket& sock, int read_size = 1024 ) :
        socket( sock ),
        min_read_size( read_size )
    {
    }

    boost::signal<void (const Ethernet::Frame&)> output;
    boost::signal<void( const Socket& sock )> socket_closed;
    boost::signal<void( const Socket& sock, int )> socket_exception;
    
    void read();

/*
public slots:
*/

    void onReadableSlot( int ) {
        read();
    }

private:

    Socket socket;
    std::vector<char> frame_buffer;
    int min_read_size;
};

#endif
