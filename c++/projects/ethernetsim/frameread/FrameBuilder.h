#ifndef FRAME_BUILDER__H
#define FRAME_BUILDER__H

#include "EthernetFrame.h"

namespace Ethernet {

class FrameBuilder
{
public:
    static Frame build( unsigned int seq,
                        unsigned int total,
                        unsigned int frame_id,
                        const std::string& from,
                        const std::string& to,
                        const std::string& data );

    static Frame build( unsigned int seq,
                        unsigned int total,
                        unsigned int frame_id,
                        const std::string& from,
                        const std::string& to,
                        const std::vector<char> data );
};

}

#endif
