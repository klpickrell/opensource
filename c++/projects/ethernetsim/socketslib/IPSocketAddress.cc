#include "IPSocketAddress.h"

IPSocketAddress::IPSocketAddress( const struct sockaddr_storage* addr ) throw( SocketException )
{
    char ipstr[ INET6_ADDRSTRLEN ];
    int port;

    if( addr->ss_family == AF_INET ) {
        // IPv4
        struct sockaddr_in* s = reinterpret_cast<struct sockaddr_in*>( const_cast<sockaddr_storage*>(addr) );
        port = ntohs( s->sin_port );
        inet_ntop( AF_INET, &s->sin_addr, ipstr, sizeof( ipstr ));

    } else if( addr->ss_family == AF_INET6 ) { 

        // IPv6
        struct sockaddr_in6* s = reinterpret_cast<struct sockaddr_in6*>( const_cast<sockaddr_storage*>(addr) );
        port = ntohs(s->sin6_port);
        inet_ntop( AF_INET, &s->sin6_addr, ipstr, sizeof( ipstr ));

    } else {
        throw SocketException( "unknown ss_family type in SocketAddress" );
    }
        
    m_port = port;
    m_host = ipstr;
    storage = boost::shared_ptr< struct sockaddr_storage >( new struct sockaddr_storage( *addr ) );
}

IPSocketAddress::IPSocketAddress( const std::string& host, int port, sa_family_t af ) :
    m_host( host ),
    m_port( port ),
    m_family( af )
{}

sockaddr_storage IPSocketAddress::getaddr_storage() const throw( SocketException )
{
    if( !storage ) {

        struct addrinfo* result;
        int error = ::getaddrinfo( m_host.c_str(), 0, 0, &result);
 
        if( error ) {
            throw SocketException( std::string( "error in getaddrinfo: " ) + gai_strerror(error) );
        }

        sockaddr_storage stor;
        memset( &stor, 0, sizeof( stor ) );
            
        if( m_family == AF_INET ) {
            // IPv4
            struct sockaddr_in* s = reinterpret_cast<struct sockaddr_in*>( result->ai_addr );
            s->sin_port = htons( m_port );
            s->sin_family = AF_INET;
        } else if( m_family == AF_INET6 ) { 
                
            // IPv6
            struct sockaddr_in6* s = reinterpret_cast<struct sockaddr_in6*>( result->ai_addr );
            s->sin6_port = htons( m_port );
            s->sin6_family = AF_INET6;

        } else {
            throw SocketException( "unknown ss_family type in SocketAddress" );
        }

        storage = boost::shared_ptr< struct sockaddr_storage >( new struct sockaddr_storage( stor ) );
    }

    return *storage.get();
}
