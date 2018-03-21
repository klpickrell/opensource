#ifndef _SOCKET__H
#define _SOCKET__H

#include <stdexcept>
#include <string>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <errno.h>

#include <boost/shared_ptr.hpp>

class SocketException : public std::exception
{
public:
    SocketException( const std::string& w ) :
        _what( w ){}

    ~SocketException() throw() {}

    const char* what() const throw() { return _what.c_str(); }

private:

    std::string _what;
};

class Socket
{
public:

    Socket( int domain, int type, int protocol ) throw( SocketException );
    virtual ~Socket();

    void setFlags( int flags ) throw( SocketException );
    int getFlags() const throw( SocketException );

    void setBlocking( bool blocking=true ) throw( SocketException );
    bool isBlocking() const throw( SocketException );

    int sock() const throw( SocketException ) {
        if( !descriptor ) {
            throw SocketException( "Socket::descriptor: invalid descriptor" );
        }

        return descriptor->sock();
    }
    
    bool eof() const throw( SocketException ) {
        char buf;
        ssize_t retval = recv( sock(), &buf, 1, MSG_PEEK );
        if( retval == 0 ) {
            return true;
        } else {
            if( errno != EWOULDBLOCK &&
                errno != EINTR ) {
                throw SocketException( std::string( "eof error: " ) + strerror( errno ) );
            }
        }

        return false;
    }

    template< typename T > 
    T getpeername() const throw( SocketException );

    template< typename T > 
    T getsockname() const throw( SocketException );

private:

    class SocketResource {
    public:
        SocketResource( int desc ) :
            descriptor( desc )
        {}
        ~SocketResource() 
        {
            close( descriptor );
        }

        int sock() const { return descriptor; }

    private:
        int descriptor;
    };

private:

    explicit Socket( int descriptor ) :
        descriptor( new SocketResource( descriptor ) )
    {}

    boost::shared_ptr< SocketResource > descriptor;
    
    friend class SocketServer;
};


template< typename T > 
T Socket::getpeername() const throw( SocketException )
{
    if( sock() < 0 ) {
        throw SocketException( "Socket::getpeername called on invalid socket" );
    }

    struct sockaddr_storage addr;
    socklen_t length = sizeof( addr );
    if( ::getpeername( sock(),
                       reinterpret_cast<struct sockaddr*>(&addr),
                       &length ) < 0 ) {
        throw SocketException( std::string( "getpeername failed: " ) + strerror( errno ) );
    }

    return T( &addr );
}

template< typename T >
T Socket::getsockname() const throw( SocketException )
{
    if( sock() < 0 ) {
        throw SocketException( "Socket::getpeername called on invalid socket" );
    }

    struct sockaddr_storage addr;
    socklen_t length = sizeof( addr );
    if( ::getsockname( sock(),
                       reinterpret_cast<struct sockaddr*>(&addr),
                       &length ) < 0 ) {
        throw SocketException( std::string( "getsockname failed: " ) + strerror( errno ) );
    }

    return T( &addr );
}

bool operator==( const Socket& lhs, const Socket& rhs );

std::ostream& operator<<( std::ostream& lhs, const Socket& rhs );

#endif
