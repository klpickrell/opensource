#include <iostream>
#include <fstream>

#include "SocketServer.h"
#include "Select.h"
#include "IPSocketAddress.h"

#include "SPConnection.h"
#include "EthernetBus.h"

#include <iosfwd>
#include "boost/program_options.hpp"
#include "boost/bind.hpp"

using namespace std;

namespace po = boost::program_options;

ofstream logger;

// ConnectionEvent is triggered when the server socket is readable
// It then calls accept, and creates a new SPConnection for the socket

class ConnectionEvent
{
public:
    ConnectionEvent( const SocketServer& serv ) :
        server( serv ){}

    void connect( int sock ) {
        Socket thesocket = server.accept();
        cout << "cbp detected connection: " << thesocket.getpeername< IPSocketAddress >().host() << endl;
        SPConnection::create( thesocket );
        cout << SPConnection::connections().size() << " total SP connections" << endl;
    }

private:
    SocketServer server;
};

using namespace std;

int main( int argc, char** argv )
{
    // command line options
    po::options_description description( "usage: cbp <options>" );
    description.add_options()
        ( "help", "This help message" )
        ( "port,p", po::value<int>(), "Specify listen port" )
        ( "log-file,l", po::value<string>(), "cbp log file output destination" );

    po::variables_map options;
    po::store( po::parse_command_line( argc, argv, description ), options );
    po::notify( options );

    if( options.count( "help" ) ) {
        cout << description << endl;
        return 1;
    }

    // initialize the logger
    string logger_file = "cbp_log.txt";
    if( options.count( "log-file" ) ) {
        logger_file = options[ "log-file" ].as<string>();
    }
    cout << "using logger output file: " << logger_file << endl;
    logger.open( logger_file.c_str(), ios::out );


    int port = 5000;
    if( options.count( "port" ) ) {
        port = options[ "port" ].as<int>();
        cout << "using port " << port << endl;
    } else {
        cout << "defaulting to port 5000" << endl;
    }

    SocketServer server( "localhost", port );
    server.setBlocking( false );

    SelectManager::instance()->add( server.listenSocket().sock(),
                                    SelectManager::Readable,
                                    boost::bind( &ConnectionEvent::connect,
                                                 ConnectionEvent( server ),
                                                 _1 ));


    bool done = false;
    while( !done ) {
        try {
            SelectManager::instance()->select( true, 1.0 );
            Ethernet::EthernetBus::instance()->flush();
            usleep( 10000 );
        } catch( const std::exception& ex ) {
            cerr << "exception in cbp.cc:main:" << ex.what() << endl;
        }
    }

    return 0;
}


