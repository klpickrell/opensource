#include "SocketWriter.h"

using namespace std;

void SocketWriter::write( const vector<char>& buffer )
{
    write_buffer.reserve( write_buffer.size() + buffer.size() );
    std::copy( buffer.begin(), buffer.end(),
               back_inserter( write_buffer ) );
    flush();
}

void SocketWriter::flush()
{
    if( write_buffer.empty() )
        return;

    ssize_t bytes_sent = send( socket.sock(),
                               &write_buffer[0],
                               write_buffer.size(),
                               0 );
    if( bytes_sent < 0 ) {

        if( errno == EAGAIN ||
            errno == EWOULDBLOCK ||
            errno == EINTR ) {
            return;
        }

        if( errno == ECONNRESET ||
            errno == ENOTCONN ) {
            socket_closed( socket );
        }

        socket_exception( socket, errno );
        
    } else if( bytes_sent >= write_buffer.size() ) {
        clear();
    } else {
        write_buffer.erase( write_buffer.begin(),
                            write_buffer.begin() + bytes_sent );
    }
}
