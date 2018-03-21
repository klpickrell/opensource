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

void sigint_handler( int stat );

bool done = false;

int main( int argc, char** argv )
{
    // set up signal handling
    struct sigaction sigact;
    memset( &sigact, 0, sizeof( sigact ) );

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

    sockaddr_in sockadd;
    memset( &sockadd, 0, sizeof( sockadd ) );

    sockadd.sin_port = htons( 51111 );
    sockadd.sin_family = AF_INET;
    sockadd.sin_addr.s_addr = inet_addr( "192.168.0.60" );

    errno = 0;
    if( bind( sock1, (sockaddr*)&sockadd, sizeof( sockadd ) ) == -1 ) {
      cerr << "bind failure with errno=" << strerror( errno ) << endl;
      return 1;
    } else {
      cout << "bound the socket" << endl;
    }

    errno = 0;
    if( listen( sock1, 5 ) == -1 ) {
      cerr << "listen failed with errno=" << strerror( errno ) << endl;
    } else {
      cout << "did a listen on the socket" << endl;
    }

    int client_sock = -1;
    while( !done ) {

      fd_set listens;
      FD_ZERO( &listens );
      FD_SET( sock1, &listens );

      struct timeval tv;
      tv.tv_sec = 0;
      tv.tv_usec = 100000;
      
      if( select( sock1+1, &listens, 0, 0, &tv ) > 0 ) {

	cout << "a socket is now readable" << endl;
	if( FD_ISSET( sock1, &listens ) ) {
	  cout << "its our listen socket!" << endl;
	  
	  sockaddr_in clientaddr;
	  int caddrlen = sizeof( clientaddr );
	  memset( &clientaddr, 0, sizeof( clientaddr ) );
	  
	  errno = 0;
	  client_sock = accept( sock1, (sockaddr*)&clientaddr, (socklen_t*)&caddrlen );
	  if( client_sock == -1 ) {
	    cout << "failed to accept socket connection! with error: " << strerror( errno ) << endl;
	  } else {
	    ostringstream os;
	    os << "a client connected!" << endl;
	    os << "port=" << ntohs( clientaddr.sin_port ) << endl;
	    os << "address=" << inet_ntoa( clientaddr.sin_addr ) << endl;
	    cout << os.str();
	  }
	}
      }
    }

    shutdown( sock1, SHUT_RDWR );
    close( sock1 );
    if( client_sock != -1 ) {
      shutdown( client_sock, SHUT_RDWR );
      close( client_sock );
    }

    return 0;
}
void sigint_handler( int stat )
{
    cout << "sigint caught, exiting" << endl;
    done = true;
}
