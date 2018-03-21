#include <iostream>
#include <fstream>

#include "Socket.h"
#include "Select.h"
#include "IPSocketAddress.h"
#include "Timer.h"
#include "CBPConnection.h"
#include "BEBOAlgorithm.h"
#include "FrameScript.h"

#include "boost/bind.hpp"

#include <iosfwd>
#include "boost/program_options.hpp"

using namespace std;

namespace po = boost::program_options;

ofstream logger;

class ConnectionMonitor
{
public:
    ConnectionMonitor( int timeout ) :
        timer( timeout )
    {
        _connected = false;
    }

    void connect( int ) { _connected = true; }
    bool connected() const { return _connected; }
    
    bool timedout() const { return timer.expired(); }

private:

    Timer timer;
    bool _connected;
};

int main( int argc, char** argv )
{
    // command line options

    po::options_description description( "usage: sp <options>" );
    description.add_options()
        ( "help", "This help message" )
        ( "port,p", po::value<int>(), "Specify connection port" )
        ( "name,n", po::value<string>(), "sp name" )
        ( "file,f", po::value<string>(), "sp input frame script file" )
        ( "slot,s", po::value<double>(), "gives ethernet slot time" )
        ( "log-file,l", po::value<string>(), "sp log file output destination" );

    po::variables_map options;
    po::store( po::parse_command_line( argc, argv, description ), options );
    po::notify( options );

    if( options.count( "help" ) ) {
        cout << description << endl;
        return 1;
    }

    // initialize the logger
    string logger_file = "sp_log.txt";
    if( options.count( "log-file" ) ) {
        logger_file = options[ "log-file" ].as<string>();
    }

    cout << "using logger output file: " << logger_file << endl;
    logger.open( logger_file.c_str(), ios::out );

    string name;
    if( options.count( "name" ) ) {
        name = options[ "name" ].as<string>();
        cout << "using name: " << name << endl;
    } else {
        cerr << "missing required argument <name,n>" << endl;
        cout << description << endl;
        return 1;
    }

    int port = 5000;
    if( options.count( "port" ) ) {
        port = options[ "port" ].as<int>();
        cout << "using port: " << port << endl;
    } else {
        cout << "defaulting to port " << port << endl;
    }

    string filename;
    if( options.count( "file" ) ) {
        filename = options[ "file" ].as<string>();
        cout << "using input file " << filename << endl;
    } else {
        cerr << "missing required argument <name,n>" << endl;
        cout << description << endl;
        return 1;
    }

    double slot_time = 0.1;
    if( options.count( "slot" ) ) {
        slot_time = options[ "slot" ].as<double>();
        cout << "using slot time: " << slot_time << endl;
    } else {
        cout << "defaulting to slot_time" << slot_time << endl;
    }
    
    Socket socket( AF_INET, SOCK_STREAM, 0 );

    socket.setBlocking( false );
    
    sockaddr_in addr;
    memset( &addr, 0, sizeof(addr) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );

    const char* remote_hostname = "127.0.0.1";
    if( inet_pton( AF_INET, remote_hostname, &addr.sin_addr ) == 0 ) {
        cerr << "unable to convert address " << remote_hostname << endl;
        return 1;
    }

    
    ConnectionMonitor connection( 20 );
    SelectManager::instance()->add( socket.sock(),
                                    SelectManager::Writeable,
                                    boost::bind( &ConnectionMonitor::connect,
                                                 &connection,
                                                 _1 ) );


    int cresult = connect( socket.sock(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr) );
    if( cresult == -1 ) {
        if( errno != EINTR &&
            errno != EINPROGRESS &&
            errno != EALREADY ) {
            cerr << "connect failure: " << strerror( errno ) << endl;
            return 1;
        }

        while( !connection.connected() ) {

            if( connection.timedout() ) {
                cerr << "timeout on non-blocking connect to " << remote_hostname << endl;
                return 1;
            }

            SelectManager::instance()->select( true, 1.0 );
            usleep( 10000 );
        }
    }

    cout << "successfully connected to " << remote_hostname << endl;

    SelectManager::instance()->remove( socket.sock(), SelectManager::Writeable );

    boost::shared_ptr<CBPConnection> cbp_connection( new CBPConnection( socket, name ) );
    cbp_connection->sendInitMsg();

    BEBOAlgorithm protocol( cbp_connection, slot_time );

    FrameScript sequence( filename );
    
    for( FrameScript::iterator it = sequence.begin();
         it != sequence.end();
         ++it ) {
        protocol.send( *it );
    }

    while( cbp_connection->connected() ) {
        SelectManager::instance()->select( true, 1.0 );
        protocol.run();
        usleep( 10000 );
    }

    cout << name << " disconnected from cbp, exiting" << endl;

    return 0;
}


