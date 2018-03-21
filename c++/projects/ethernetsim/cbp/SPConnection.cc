#include "SPConnection.h"
#include "Select.h"
#include "EthernetBus.h"

#include "logger.h"

#include <iostream>

using namespace std;
using namespace Ethernet;

list<boost::shared_ptr<SPConnection> > SPConnection::_connections;

SPConnection::SPConnection( const Socket& sock, const string& s_id ) :
    socket( sock ),
    _id( s_id ),
    reader( sock ),
    writer( sock )
{
    reader.output.connect( boost::bind( &SPConnection::onFrameSlot,
                                        this,
                                        _1 ) );

    reader.socket_closed.connect( boost::bind( &SPConnection::onCloseSlot,
                                               this,
                                               _1 ) );

    reader.socket_exception.connect( boost::bind( &SPConnection::onExceptionSlot,
                                                  this,
                                                  _1, _2 ) );

    writer.socket_closed.connect( boost::bind( &SPConnection::onCloseSlot,
                                               this,
                                               _1 ) );

    writer.socket_exception.connect( boost::bind( &SPConnection::onExceptionSlot,
                                                  this,
                                                  _1, _2 ) );

    SelectManager::instance()->add( socket.sock(),
                                    SelectManager::Readable,
                                    boost::bind( &FrameReader::onReadableSlot,
                                                 &reader,
                                                 _1 ) );

    cout << "created SPConnection" << endl;
    add();
}

SPConnection::~SPConnection()
{
    cout << "closing SPConnection " << (_id.length()?_id:"") << endl;
    SelectManager::instance()->remove( socket.sock() );
}

void SPConnection::onFrameSlot( const Ethernet::Frame& frame )
{
    //    logger << "CBP received frame: " << frame << " on " << socket << endl;
    //    logger.flush();

    if( frame.to() == "cbp" ) {
        setID( frame.from() );
        logger << "SPConnection initialized for " << id() << endl;
        logger.flush();
        return;
    }

    if( id().empty() ) {
        logger << "CBP received frame on uninitialized SPConnection! discarding" << endl;
        logger.flush();
        return;
    }

    if( frame.from() == id() ) {
        EthernetBus::instance()->send( frame );
    } else {
        logger << id() << " received frame not intended for it!" << endl;
        logger.flush();
    }
}
