#include <algorithm>
#include <iostream>

#include "SocketReader.h"

using namespace std;

void SocketReader::read()
{
    try {
        if( socket.eof() ) {
            socket_closed( socket );
            return;
        }
    } catch( const SocketException& ex ) {
        return;
    }

    vector<char> read_buffer;
    read_buffer.resize( min_read_size );

    ssize_t bytes = recv( socket.sock(),
                          &read_buffer[0],
                          read_buffer.size(),
                          0 );
    if( bytes < 0 ) {

        // what to do here?
        if( errno == EWOULDBLOCK ||
            errno == EAGAIN ||
            errno == EINTR ) {
            return;
        }

        socket_exception( socket, errno );

    } else if( bytes == 0 ) {
        socket_closed( socket );
    } else {
        cout << "SocketReader read " << bytes << " bytes from socket" << endl;
        output( read_buffer );
    }
}
