#ifndef SOCKET_SERVER__H
#define SOCKET_SERVER__H

#include "Socket.h"

#include <boost/function.hpp>

#include <string>

class SocketServer
{
public:
    
    SocketServer( const std::string& host,
                  int port,
                  int backlog=5,
                  const Socket& sock = Socket( AF_INET, SOCK_STREAM, 0 ) ) throw( SocketException );

    void setBlocking( bool blocking ) throw( SocketException ) {
        return serverSocket.setBlocking( blocking );
    }

    bool isBlocking() const throw( SocketException ) {
        return serverSocket.isBlocking();
    }

    Socket accept() const throw( SocketException );

    Socket listenSocket() const {
        return serverSocket;
    }

private:

    Socket serverSocket;
    std::string host;
    int port;
};

#endif
