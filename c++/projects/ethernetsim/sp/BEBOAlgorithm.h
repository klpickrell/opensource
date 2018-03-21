#ifndef BEBO_ALGORITHM__H
#define BEBO_ALGORITHM__H

#include "CBPConnection.h"
#include "boost/shared_ptr.hpp"
#include "Timer.h"
#include "FrameAccumulator.h"

#include <exception>
#include <map>

class BEBOException : public std::exception
{
public:
    BEBOException( const std::string& wh ) :
        _what( wh )
    {}
    ~BEBOException() throw(){}
    const char* what() const throw() { return _what.c_str(); }
private:
    std::string _what;
};


class BEBOAlgorithm
{
public:

    BEBOAlgorithm( boost::shared_ptr<CBPConnection> cbp_connection, double slot_time )
        throw( BEBOException );

    void send( const Ethernet::Frame& frame );
    void BEBOAlgorithm::onFrameSlot( const Ethernet::Frame& frame );

    void run();

    typedef std::list< boost::shared_ptr< Ethernet::Frame > > ListType;

private:

    boost::shared_ptr<CBPConnection> cbp_connection;
    ListType output_queue;
    Timer    bebo_timer;
    Timer    slot_timer;

    double slot_time;
    int collision_count;

    enum { FREE, WAITING, BACKOFF } state;

    typedef std::map< std::string, boost::shared_ptr<FrameAccumulator> > InputMap;
    InputMap input_queue;
};

#endif
