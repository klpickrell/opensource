#include <iostream>
#include <cmath>

#include "boost/bind.hpp"

#include "BEBOAlgorithm.h"
#include "logger.h"
#include <iomanip>

using namespace std;

// The BEBOAlgorithm class controls the running of the binary exponential backoff.
// It manages a single connection to the CBP called cbp_connection.  onFrameSlot
// is called when the CBPConnection receives a full frame.  Each frame is
// accumulated by a FrameAccumulator which checks that the frames are coherent (out of sequence).
// If frames are not coherent, as can occur when the CBP drops the second part of a record due
// to collision after the first part has been received, FrameAccumulator throws an exception
// that triggers the clearing of the corresponding input queue.

// The bulk of the BEBO logic is contained in the 'run' method below

BEBOAlgorithm::BEBOAlgorithm( boost::shared_ptr< CBPConnection > conn, double stime ) throw( BEBOException )
    : cbp_connection( conn ),
      state( FREE )
{
    cbp_connection->getInput().connect( boost::bind( &BEBOAlgorithm::onFrameSlot,
                                                    this,
                                                    _1 ) );
    if( stime >= 0.0 ) {
        slot_time = stime;
    } else {
        throw BEBOException( "cannot initialize algorithm with negative slot time" );
    }

    collision_count = 0;
    slot_timer.set( slot_time );

    srand( static_cast< int >( Timer::now_ns() ) );
}

// onFrameSlot is called when a frame is received from the cbp

void BEBOAlgorithm::onFrameSlot( const Ethernet::Frame& frame )
{
    logger << cbp_connection->name() << " received frame: " << frame << endl;
    
    InputMap::iterator i = input_queue.find( frame.from() );
    if( i == input_queue.end() ) {
        input_queue[ frame.from() ] = 
            boost::shared_ptr< FrameAccumulator >
            ( new FrameAccumulator );
    }

    try {
        input_queue[ frame.from() ]->add( frame );
    } catch( const Ethernet::FormatError& ex ) {
        cout << cbp_connection->name() << " detected frame gap" << endl;
        logger << cbp_connection->name() << " detected frame gap" << endl;
        input_queue[ frame.from() ]->clear();
    }

    for( InputMap::iterator iq = input_queue.begin();
         iq != input_queue.end();
         ++iq ) {

        // if all of the frames have been received
        if( !iq->second->complete() ) {
            continue;
        }

        // grab all of the message data to determine what kind it is, it could be a collision
        vector<char> input_frame_buffer = iq->second->getMessageData();
        iq->second->clear();

        boost::shared_ptr<char> sdata( strndup( reinterpret_cast<char*>(&input_frame_buffer[0]),
                                                input_frame_buffer.size() ),
                                       free );
        if( sdata ) {
            logger << cbp_connection->name() << " received message: " << sdata.get() << endl;
            logger << flush;
        }

        // if it is a collision message

        if( string( sdata.get() ) == "collision"  ) {
            collision_count++;
            // wait ((rand() % 2^collision_count)+1) * slot_time seconds
            int num_slots = (rand() % static_cast<int>(pow( static_cast<double>(2), collision_count ))) + 1;
            double time = num_slots * slot_time;
            
            logger << cbp_connection->name()
                   << " notified of collision #" << collision_count << ", will wait for "
                   << num_slots << " time slots" << endl;
            logger << flush;

            cout << cbp_connection->name()
                 << " notified of collision #" << collision_count << ", will wait for "
                 << num_slots << " time slots" << endl;

            // start the backoff
            state = BACKOFF;
            bebo_timer.set( time );
        }
    }
}

// put the mesasge onto the queue and try to output it when we can
void BEBOAlgorithm::send( const Ethernet::Frame& frame ) 
{
    output_queue.push_back( boost::shared_ptr<Ethernet::Frame>( new Ethernet::Frame( frame ) ) );
}

// The run method deals with 3 states:
//    FREE: We can try to send a message immediately
//    WAITING: We have tried to send a message and must wait until the end of the slot time
//    BACKOFF: We have detected a collision and should wait until the bebo_timer has expired

void BEBOAlgorithm::run()
{
    switch( state ) {

    case FREE:
        {
            if( output_queue.empty() ) {
                break;
            }

            boost::shared_ptr<Ethernet::Frame> frame = output_queue.front();
            logger << cbp_connection->name()
                   << " sending part "
                   << frame->sequence_num()
                   << " of frame " << frame->frame_id()
                   << " to " << frame->to() << endl;
            logger << flush;

            cout << cbp_connection->name()
                 << " sending part "
                 << frame->sequence_num()
                 << " of frame " << frame->frame_id()
                 << " to " << frame->to() << endl;

            cbp_connection->send( *frame );
            slot_timer.set( slot_time );
            state = WAITING;
        }
        break;

    case WAITING:
        {
            if( slot_timer.expired() ) {

                cout << "slot time expired" << endl;
                logger << "slot time expired" << endl;

                if( !output_queue.empty() ) {
                    output_queue.pop_front();
                    cout << "removed message from output queue" << endl;
                    logger << "removed message from output queue" << endl;
                }

                collision_count = 0;
                state = FREE;
            }
        }
        break;

    case BACKOFF:
        {
            if( bebo_timer.expired() ) {
                cout << "Backoff time expired, continuing" << endl;
                logger << "Backoff time expired, continuing" << endl;
                state = FREE;
            }
        }
        break;

    default:break;

    }
}
