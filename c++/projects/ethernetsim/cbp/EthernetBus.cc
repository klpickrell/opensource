#include "EthernetBus.h"
#include "SPConnection.h"
#include "FrameBuilder.h"
#include "logger.h"

#include <iostream>

using namespace std;
using namespace Ethernet;

// The EthernetBus class is the single point at which messages received
// from any of the SPConnections route their messages.  It then
// performs necessary routing and collision detection on all incoming
// frames.

// The send function accepts a frame and either holds it on the bus
// or detects a collision

void EthernetBus::send( const Frame& frame )
{
    logger << "Receive part " << frame.sequence_num() << " of frame " << frame.frame_id()
           << " from " << frame.from() << ", to " << frame.to() << endl;
    logger.flush();

    if( !bus ) {
        bus.reset( new Frame( frame ) );
        return;
    }

    if( bus->to() == frame.to() &&
        bus->from() == frame.from() ) {

        SPConnection::iterator it;
        for( SPConnection::iterator it = SPConnection::begin();
             it != SPConnection::end();
             ++it ) {

            if( (*it)->id() == frame.to() ) {
                break;
            }
        }

        if( it != SPConnection::end() ) {
            outgoing2 = outgoing1;
            outgoing1 = bus;
            bus.reset( new Frame( frame ) );
        } else {
            logger << "no SPConnection found with id: " << frame.to() << endl;
        }
    } else {
        // a collision occurred 

        logger << "Collision detected" << endl;

        // construct collision notification, notify frame.from() and bus->from()
        SPConnection::iterator it;
        for( it = SPConnection::begin();
             it != SPConnection::end();
             ++it ) {

            if( (*it)->id() == frame.from() ||
                (*it)->id() == bus->from() ) {
                Frame collision = FrameBuilder::build( 1,1,1,
                                                       "cbp",
                                                       (*it)->id(),
                                                       "collision" );
                (*it)->send( collision );

                logger << "Inform " << (*it)->id() << " of collision" << endl;
                logger.flush();
            }
        }

        if( it != SPConnection::end() ) {
            // also inform all stations in the outgoing queue that their messages collided

            if( outgoing1 ) {

                Frame collision = FrameBuilder::build( 1,1,1,
                                                       "cbp",
                                                       outgoing1->from(),
                                                       "collision" );
                (*it)->send( collision );

                logger << "Inform " << outgoing1->from() << " of collision" << endl;
                logger.flush();
            }

            if( outgoing2 ) {

                Frame collision = FrameBuilder::build( 1,1,1,
                                                       "cbp",
                                                       outgoing2->from(),
                                                       "collision" );
                (*it)->send( collision );

                logger << "Inform " << outgoing2->from() << " of collision" << endl;
                logger.flush();
            }
        }

        outgoing1.reset();
        outgoing2.reset();
        bus.reset();
    }
}

// flush sends out one record and then returns
void EthernetBus::flush()
{
    if( !outgoing2 && !outgoing1 ) {
        return;
    }
    
    if( outgoing1 && !outgoing2 ) {
        outgoing2 = outgoing1;
        outgoing1.reset();
    }

    SPConnection::iterator it;
    for( it = SPConnection::begin();
         it != SPConnection::end();
         ++it ) {

        if( (*it)->id() == outgoing2->to() ) {
            break;
        }
    }

    if( it != SPConnection::end() ) {
        logger << "Transfer part " << outgoing2->sequence_num() << " of frame " << outgoing2->frame_id()
               << " from " << outgoing2->from() << ", to " << outgoing2->to() << endl;
        logger.flush();
        (*it)->send( *outgoing2 );
        outgoing2.reset();
    } else {
        logger << __FILE__ << ":" << __LINE__ << "  " << __FUNCTION__ << " - no SPConnection found with id: " << outgoing2->to() << endl;
        outgoing2.reset();
    }
}
