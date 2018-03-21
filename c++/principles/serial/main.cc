#include <iostream>
#include <sstream>

// for struct termios
#include <termios.h>

// for sigaction
#include <signal.h>

// for select
#include <sys/select.h>

// for socket
#include <sys/socket.h>
#include <sys/types.h>

// sockaddr_in
#include <netinet/in.h>

// inet_addr
#include <arpa/inet.h>

// errno
#include <errno.h>

// fcntl
#include <fcntl.h>

using namespace std;

void sigio_handler( int stat );
void sigint_handler( int stat );

bool ready_for_read = true;
bool done = false;

int main( int argc, char** argv )
{
    // set up signal handling
    struct sigaction sigact;
    memset( &sigact, 0, sizeof( sigact ) );

    /*
    sigact.sa_handler = sigio_handler;
    sigemptyset( &sigact.sa_mask );

    if( sigaction( SIGIO, &sigact, 0 ) < 0 ) {
	cerr << "error setting signal handler for SIGIO" << endl;
	return 1;
    }
    */

    sigact.sa_handler = sigint_handler;
    sigemptyset( &sigact.sa_mask );
    
    if( sigaction( SIGINT, &sigact, 0 ) < 0 ) {
	cerr << "error setting signal handler for SIGINT" << endl;
	return 1;
    }

    // open and set up serial handling
    //    struct termios oldtio, newtio;
    //    memset( &newtio, 0, sizeof( newtio ) );

    int sock1 = socket( AF_INET, SOCK_STREAM, 0 );
    if( sock1 == -1 ) {
	cout << "Error opening socket" << endl;
	return 1;
    }

    int sock2 = socket( AF_INET, SOCK_STREAM, 0 );
    if( sock2 == -1 ) {
	cout << "Error opening socket" << endl;
	return 1;
    }

    sockaddr_in saddr1;
    sockaddr_in saddr2;
    memset( &saddr1, 0, sizeof( saddr1 ) );
    memset( &saddr2, 0, sizeof( saddr2 ) );

    saddr1.sin_family = AF_INET;
    saddr1.sin_port = htons( 50000 );
    saddr1.sin_addr.s_addr = inet_addr( "192.168.0.60" );

    saddr2.sin_family = AF_INET;
    saddr2.sin_port = htons( 50001 );
    saddr2.sin_addr.s_addr = inet_addr( "192.168.0.60" );

    errno = 0;
    int constat = connect( sock1, (sockaddr*) &saddr1, sizeof( sockaddr ) );
    if( constat != 0 ) {
	ostringstream os;
	os << "error connecting socket 1 to port 50000.  errno=" << strerror( errno ) << endl;
	cout << os.str();
    } else {
	cout << "socket 1 connected" << endl;
    }

    errno = 0;
    constat = connect( sock2, (sockaddr*) &saddr2, sizeof( sockaddr ) );
    if( constat != 0 ) {
	ostringstream os;
	os << "error connecting socket 2 to port 50001.  errno=" << strerror( errno ) << endl;
	cout << os.str();
    } else {
	cout << "socket 2 connected" << endl;
    }
    
    /*
    fcntl( sock1, F_SETOWN, getpid() );
    fcntl( sock1, F_SETFL, O_ASYNC );
    
    fcntl( sock2, F_SETOWN, getpid() );
    fcntl( sock2, F_SETFL, O_ASYNC );
    */

    fcntl( sock1, F_SETFL, O_NONBLOCK );
    fcntl( sock2, F_SETFL, O_NONBLOCK );

    fd_set sockfds;
    FD_ZERO( &sockfds );

    timeval tv;
    
    while( !done ) {

	tv.tv_sec = 0;
	tv.tv_usec = 10000;

	FD_SET( sock1, &sockfds );
	FD_SET( sock2, &sockfds );

	if( ready_for_read ) {
	    errno = 0;
	    int sel_stat = select( max( sock1, sock2 ) + 1,
				   &sockfds,
				   0,
				   0,
				   0 );
	    if( errno != 0 ) {
		cout << "errno returned: " << strerror( errno ) << endl;
	    } else {

		if( FD_ISSET( sock1, &sockfds ) ) {
		    cout << "sock1 ready for reading..." << endl;
		    
		    char recvbuf[256];
		    int stat = recv( sock1, &recvbuf, sizeof( recvbuf ), 0 );
		    if( stat == 0 || stat == -1 ) {
			cout << "recv returned " << (stat==0?"0":"-1") << ", socket closing..." << endl;
			shutdown( sock1, SHUT_RDWR );
			close( sock1 );
			FD_CLR( sock1, &sockfds );
			sock1 = -1;
		    } else {
			char* bvals = new char[ stat+1 ];
			memcpy( bvals, recvbuf, stat );
			bvals[stat] = 0;
			ostringstream os;
			os << "recv read " << stat << " bytes: " << string( bvals ) << endl;
			cout << os.str() << endl;
			delete[] bvals;
		    }
		}

		if( FD_ISSET( sock2, &sockfds ) ) {
		    cout << "sock2 ready for reading..." << endl;

		    char recvbuf[256];
		    int stat = recv( sock2, &recvbuf, sizeof( recvbuf ), 0 );
		    if( stat == 0 || stat == -1 ) {
			cout << "recv returned " << (stat==0?"0":"-1") << ", socket closing..." << endl;
			shutdown( sock2, SHUT_RDWR );
			close( sock2 );
			FD_CLR( sock2, &sockfds );
			sock2 = -1;
		    } else {
			char* bvals = new char[ stat+1 ];
			memcpy( bvals, recvbuf, stat );
			bvals[stat] = 0;
			ostringstream os;
			os << "recv read " << stat << " bytes: " << string( bvals ) << endl;
			cout << os.str() << endl;
			delete[] bvals;
		    }
		}
	    
		//		ready_for_read = false;
	    }
	}
    }

    close( sock1 );
    close( sock2 );

    return 0;
}
void sigio_handler( int stat )
{
    cout << "got a sigio" << endl;
    ready_for_read = true;
}
void sigint_handler( int stat )
{
    cout << "sigint caught, exiting" << endl;
    done = true;
}
