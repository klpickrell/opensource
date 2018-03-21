#include "FrameReader.h"

#include <algorithm>

#include <iostream>

using namespace std;

void FrameReader::read()
{
    try {
        if( socket.eof() ) {
            socket_closed( socket );
            return;
        }
    } catch( const SocketException& ex ) {
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
        cout << "FrameReader read " << bytes << " bytes from socket" << endl;
        std::copy( read_buffer.begin(), 
                   read_buffer.begin() + bytes, 
                   back_inserter( frame_buffer ) );

        cout << "frame_buffer size is now " << frame_buffer.size() << endl;

        while( frame_buffer.size() >= Ethernet::FRAME_HEADER_LENGTH ) {
            Ethernet::Header* header = reinterpret_cast<Ethernet::Header*>( &frame_buffer[0] );
            unsigned int totalsize = Ethernet::FRAME_HEADER_LENGTH + ntohl( header->data_length );
            if( frame_buffer.size() >= totalsize ) {
                Ethernet::Frame frame( &frame_buffer[0], totalsize, Ethernet::BYTE_ORDER_NETWORK );
                cout << "FrameReader got frame buffer: " << frame << endl;
                output( frame );
                //erase 0..totalsize-1
                frame_buffer.erase( frame_buffer.begin(),
                                    frame_buffer.begin()+totalsize );

                cout << "frame_buffer size is now " << frame_buffer.size() << endl;
            } else {
                break;
            }
        }
    }
}
