#include "Socket.h"

#include <boost/bind.hpp>

#include <ostream>

// Unix specific includes
#include <errno.h>
#include <fcntl.h>

using namespace std;

Socket::Socket( int domain, int type, int protocol ) throw( SocketException )
{
    int sock = socket( domain, type, protocol );
    if( sock < 0 ) {
        throw SocketException( std::string( strerror( errno ) ) );
    }

    descriptor.reset( new SocketResource( sock ) );
}

Socket::~Socket()
{
}

void Socket::setFlags( int flags ) throw( SocketException )
{
    if( sock() < 0 ) {
        throw SocketException( "Socket::setFlags called on invalid socket" );
    }

    if( fcntl( sock(), F_SETFL, flags ) < 0 ) {
        throw SocketException( string( "fcntl failed on F_SETFL: " ) + strerror( errno ) );
    }
}

int Socket::getFlags() const throw( SocketException )
{
    if( sock() < 0 ) {
        throw SocketException( "Socket::getFlags called on invalid socket" );
    }

    int flags;
    if( flags = fcntl( sock(), F_GETFL, 0 ) < 0 ) {
        throw SocketException( string( "fcntl failed on F_GETFL: " ) + strerror( errno ) );
    }
    
    return flags;
}

void Socket::setBlocking( bool block ) throw( SocketException )
{
    if( block ) {
        setFlags( getFlags() & ~O_NONBLOCK );
    } else {
        setFlags( getFlags() | O_NONBLOCK );
    }
}

bool Socket::isBlocking() const throw( SocketException )
{
    return (getFlags() & O_NONBLOCK) != 0;
}

bool operator==( const Socket& lhs, const Socket& rhs )
{
    return lhs.sock() == rhs.sock();
}

ostream& operator<<( ostream& lhs, const Socket& rhs )
{
    lhs << "socket: " << rhs.sock();
}
