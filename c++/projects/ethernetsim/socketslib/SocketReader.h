#ifndef SOCKET_READER__H
#define SOCKET_READER__H

#include <boost/signals.hpp>

#include "Socket.h"

class SocketReader : public boost::signals::trackable
{
public:
    SocketReader( const Socket& socket, int read_size = 1024 ) :
        socket( socket ),
        min_read_size( read_size )
    {}

    boost::signal<void (const std::vector<char>&) > output;
    boost::signal<void (const Socket&) > socket_closed;
    boost::signal<void (const Socket&, int) > socket_exception;

    void onReadableSlot( int ) {
        read();
    }

private:

    void read();

    Socket socket;
    int min_read_size;
};

#endif
