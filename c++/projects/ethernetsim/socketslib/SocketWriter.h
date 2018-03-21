#ifndef SOCKET_WRITER__H
#define SOCKET_WRITER__H

#include <boost/signals.hpp>
#include <vector>

#include "Socket.h"

class SocketWriter : public boost::signals::trackable
{
public:
    SocketWriter( const Socket& socket ) :
        socket( socket )
    {}

    void write( const std::vector<char>& buffer );
    void flush();

    void clear() { write_buffer.clear(); }

    int bytes_queued() const { return write_buffer.size(); }

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
    std::vector<char> write_buffer;
};

#endif
