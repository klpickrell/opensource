#ifndef FRAME_ACCUMULATOR__H
#define FRAME_ACCUMULATOR__H

#include "EthernetFrame.h"
#include <vector>

class FrameAccumulator
{
public:
    FrameAccumulator();


    void add( const Ethernet::Frame& frame ) throw( Ethernet::FormatError );

    std::vector<char> getMessageData();
    bool complete() const;

    void clear() { frames.clear(); }

private:
    
    std::vector< Ethernet::Frame > frames;
};

#endif
