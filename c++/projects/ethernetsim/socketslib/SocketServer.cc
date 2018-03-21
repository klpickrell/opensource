#include "SocketServer.h"

#include <errno.h>
#include <netinet/in.h>

using namespace std;

SocketServer::SocketServer( const std::string& host, int port, int backlog, const Socket& sock ) throw( SocketException ) :
    serverSocket( sock ),
    host( host ),
    port( port )
{
    struct sockaddr_in m_addr;
    memset( &m_addr, 0, sizeof( m_addr ) );

    if( host.empty() ) {
        m_addr.sin_addr.s_addr = INADDR_ANY;
    } else {

        {
            int on = 1;
            if( setsockopt( serverSocket.sock(), SOL_SOCKET, SO_REUSEADDR,
                            reinterpret_cast<const char*>(&on), 
                            sizeof(on) ) < 0 ) {

                throw SocketException( string( "SocketServer setsockopt failure: " ) + strerror( errno ) );
            }
        }
        

        {
            linger lopt = { 0 };
            lopt.l_onoff = 1;
            lopt.l_linger = 30;
            if( setsockopt( serverSocket.sock(), SOL_SOCKET, SO_LINGER,
                            reinterpret_cast<const char*>(&lopt), 
                            sizeof(lopt) ) < 0 ) {

                throw SocketException( string( "SocketServer setsockopt failure: " ) + strerror( errno ) );
            }

        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_addr.s_addr = INADDR_ANY;
        m_addr.sin_port = htons( port );

        if( bind( serverSocket.sock(),
                  reinterpret_cast<const struct sockaddr*>(&m_addr),
                  sizeof(m_addr) ) < 0 ) {
            throw SocketException( string( "SocketServer bind failure: " ) + strerror( errno ) ) ;
        }

        if( listen( serverSocket.sock(),
                    backlog ) < 0 ) {
            throw SocketException( string( "SocketServer listen failure: " ) + strerror( errno ) );
        }
    }
}

Socket SocketServer::accept() const throw( SocketException )
{
    struct sockaddr_in client;
    int sock;
    socklen_t length = sizeof( client );
    
    sock = ::accept( serverSocket.sock(),
                     reinterpret_cast<struct sockaddr*>(&client),
                     &length );
    if( sock == -1 ) {
        throw SocketException( string( "SocketServer::accept failure: " ) + strerror( errno ) );
    }
    
    return Socket( sock );
}
