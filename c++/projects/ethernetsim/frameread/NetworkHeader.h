#ifndef NETWORK_HEADER__H
#define NETWORK_HEADER__H

#include "EthernetFrame.h"
#include <arpa/inet.h>

namespace Ethernet
{
    class NetworkHeader
    {
    public:
        NetworkHeader( unsigned int sequence_num,
                       unsigned int total_frames,
                       unsigned int frame_id,
                       const std::string& from,
                       const std::string& to,
                       unsigned int data_length ) throw( FormatError )
        {
            if( from.length() > MAX_IDENTIFIER_LENGTH ) {
                throw FormatError( std::string( "Identifier too long: " ) + from );
            }

            if( to.length() > MAX_IDENTIFIER_LENGTH ) {
                throw FormatError( std::string( "Identifier too long: " ) + to );
            }

            strncpy( header.sync, sync_string, SYNC_SIZE );
            header.sequence_num = sequence_num;
            header.total_frames = total_frames;
            header.frame_id = frame_id;            
            strcpy( header.from, from.c_str() );
            strcpy( header.to, to.c_str() );
            header.data_length = data_length;

            nbo = false;
        }

        operator Header() const {
            if( !nbo ) {
                header.sequence_num = htonl( header.sequence_num );
                header.total_frames = htonl( header.total_frames );
                header.frame_id = htonl( header.frame_id );
                header.data_length = htonl( header.data_length );
                nbo = true;
            }
            return header;
        }

    private:
        mutable Header header;
        mutable bool nbo;
    };
}

#endif
