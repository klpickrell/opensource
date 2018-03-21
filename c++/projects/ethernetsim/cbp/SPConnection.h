#ifndef SP_CONNECTION__H
#define SP_CONNECTION__H

#include <list>
#include "boost/shared_ptr.hpp"
#include "boost/bind.hpp"

#include "Socket.h"
#include "ErrnoException.h"

#include "FrameReader.h"
#include "FrameWriter.h"

class SPConnectionException : public SocketException
{
public:
    SPConnectionException( const Socket& sock,
                           const std::string& w ) :
        SocketException( w ),
        sock( sock )
    {}

    ~SPConnectionException() throw() {}

    const Socket& socket() const { return sock; }

private:
    
    Socket sock;
};

class SPConnection
{
private:
    explicit SPConnection( const Socket& sock, const std::string& _id = std::string() );

public:

    ~SPConnection();
    static void create( const Socket& sock,
                        const std::string& id = std::string() )
    {
        new SPConnection( sock,
                          id );
    }



// iterators into connections

    typedef std::list< boost::shared_ptr<SPConnection> > SPConnectionList;
    typedef SPConnectionList::iterator iterator;
    typedef SPConnectionList::const_iterator const_iterator;

    
    static iterator begin() { return _connections.begin(); }
    static iterator end() { return _connections.end(); }

    static const SPConnectionList& connections() {
        return _connections;
    }


// utility functions

    void remove() {
        _connections.remove_if( boost::bind( std::equal_to<SPConnection*>(),
                                             this,
                                             boost::bind( &boost::shared_ptr<SPConnection>::get,
                                                          _1 ) ) );
    }

    std::string id() const { return _id; }
    void setID( const std::string& newid ) { _id = newid; }

    void send( const Ethernet::Frame& frame ) {
        writer.write( frame );
    }

private:

    void add() { _connections.push_back( boost::shared_ptr<SPConnection>(this) ); }

/* 
private slots:
*/
    void onCloseSlot( const Socket& sock ) {
        if( sock == socket ) {
            remove();
        }
    }

    void onExceptionSlot( const Socket& sock, int errnoval ) {
        if( sock == socket ) {
            throw ErrnoException( errnoval, "unknown socket exception" );
        }
    }

    void onFrameSlot( const Ethernet::Frame& frame );

private:

    static SPConnectionList _connections;
    Socket socket;
    std::string _id;

    FrameReader reader;
    FrameWriter writer;
};

#endif
