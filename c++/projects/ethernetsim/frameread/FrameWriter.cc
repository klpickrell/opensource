#include "FrameWriter.h"

using namespace std;

void FrameWriter::write( const Ethernet::Frame& frame )
{
    // pack the frame into a vector<char>
    std::copy( frame.buffer().begin(), frame.buffer().end(),
               back_inserter( frame_buffer ) );
    flush();
}

void FrameWriter::flush()
{
    if( frame_buffer.empty() )
        return;

    ssize_t bytes_sent = send( socket.sock(),
                               &frame_buffer[0],
                               frame_buffer.size(),
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
        
    } else if( bytes_sent >= frame_buffer.size() ) {
        frame_buffer.clear();
    } else {
        frame_buffer.erase( frame_buffer.begin(),
                            frame_buffer.begin() + bytes_sent );
    }
}
