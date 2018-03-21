#ifndef CBP_CONNECTION__H
#define CBP_CONNECTION__H

#include "Socket.h"
#include "EthernetFrame.h"
#include "FrameReader.h"
#include "FrameWriter.h"

#include "ErrnoException.h"


class CBPConnection
{
public:

    CBPConnection( const Socket& sock, const std::string& name );

    bool connected() const {
        return !socket.eof();
    }

    void sendInitMsg();
    std::string name() const { return _name; }


/*
public slots:
*/

    
    void onWriteableSlot( int sock ) {
        if( sock == socket.sock() ) {
            writer.flush();
        }
    }

    boost::signal<void(const Ethernet::Frame&)>& getInput() {
        return reader.output;
    }

    void send( const Ethernet::Frame& frame ) {
        writer.write( frame );
    }

    bool bytesQueued() const {
        return writer.bytes_remaining() > 0;
    }

    void clearOutgoing() {
        writer.clear_buffers();
    }


private:

/*
private slots:
*/

    void onCloseSlot( const Socket& sock ) {
        if( sock == socket ) {
            // connected should handle this
        }
    }

    void onExceptionSlot( const Socket& sock, int errnoval ) {
        if( sock == socket ) {
            throw ErrnoException( errnoval, "unknown socket exception" );
        }
    }

    void onFrameSlot( const Ethernet::Frame& );

private:
    
    Socket socket;
    std::string _name;

    FrameReader reader;
    FrameWriter writer;

    std::vector<char> input_frame_buffer;
};

#endif
