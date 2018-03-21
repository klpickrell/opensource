#ifndef TCP_SOCKET__H
#define TCP_SOCKET__H

#include "Socket.h"

class TCPSocket : public Socket
{
public:

    TCPSocket() throw( SocketException ) 
        : Socket( AF_INET, SOCK_STREAM, 0 )
    {
        m_connected = false;
    }

    bool connected() const { return m_connected; }
    void connect() { m_connected = true; }

private:

    bool m_connected;
};

#endif
