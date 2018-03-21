#ifndef ETHERNET_BUS__H
#define ETHERNET_BUS__H

#include <list>
#include "singleton.h"
#include "EthernetFrame.h"
#include "Socket.h"

#include "boost/shared_ptr.hpp"

namespace Ethernet {

    class EthernetBus : public singleton< EthernetBus >
    {
        DECLARE_SINGLETON_FRIENDS( EthernetBus )

    public:

        void send( const Ethernet::Frame& frame );
        void flush();

    private:

        boost::shared_ptr< Ethernet::Frame > bus;

        boost::shared_ptr< Ethernet::Frame > outgoing1;
        boost::shared_ptr< Ethernet::Frame > outgoing2;
    };
}


#endif
