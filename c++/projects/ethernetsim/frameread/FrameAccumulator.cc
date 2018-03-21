#include "FrameAccumulator.h"

using namespace std;

FrameAccumulator::FrameAccumulator()
{}

void FrameAccumulator::add( const Ethernet::Frame& frame ) throw( Ethernet::FormatError )
{
    if( frames.empty() ) {
        frames.push_back( frame );
        return;
    }

    if( frame.to() != (frames.end()-1)->to() ||
        frame.from() != (frames.end()-1)->from() ||
        frame.frame_id() != (frames.end()-1)->frame_id() ) {
        throw Ethernet::FormatError( "attempt to accumulate frames with different headers" );
    }

    frames.push_back( frame );
}

vector<char> FrameAccumulator::getMessageData()
{
    vector<char> input_frame_buffer;
    for( vector<Ethernet::Frame>::iterator it = frames.begin();
         it != frames.end();
         ++it ) {

        vector<char> data = it->data();
        std::copy( data.begin(), data.end(),
                   back_inserter( input_frame_buffer ) );
    }
    
    return input_frame_buffer;
}

bool FrameAccumulator::complete() const
{
    if( frames.empty() ) {
        return false;
    }

    return( (frames.end()-1)->sequence_num() == (frames.end()-1)->total_frames() &&
            (frames.end()-1)->sequence_num() == frames.size() );
}
