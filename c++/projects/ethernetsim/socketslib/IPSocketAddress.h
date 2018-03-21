#ifndef IP_SOCKET_ADDRESS__H
#define IP_SOCKET_ADDRESS__H

#include <netdb.h>
#include <arpa/inet.h>

#include <boost/shared_ptr.hpp>

#include "Socket.h"

class IPSocketAddress
{
public:
    IPSocketAddress( const struct sockaddr_storage* addr ) throw( SocketException );
    IPSocketAddress( const std::string& host, int port, sa_family_t af = AF_INET );

public:
    
    std::string host() const { return m_host; }
    int port() const { return m_port; }

    sockaddr_storage getaddr_storage() const throw( SocketException );

private:

    std::string m_host;
    int m_port;
    sa_family_t m_family;
    mutable boost::shared_ptr< struct sockaddr_storage > storage;
};


#endif
