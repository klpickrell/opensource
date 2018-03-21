#include <iostream>
#include <termios.h>
#include <signal.h>
#include <sys/select.h>

using namespace std;

const int STDIN=0;

int main( int argc, char** argv )
{
    struct timeval tv;
    fd_set readers;

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    FD_ZERO( &readers );
    FD_SET( STDIN, &readers );

    select( STDIN+1, &readers, 0, 0, &tv );

    if( FD_ISSET( STDIN, &readers ) )
	cout << "you pressed a key!" << endl;
    else
	cout << "timeout!" << endl;

    return 0;
}
