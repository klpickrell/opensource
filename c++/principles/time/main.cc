#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
int main( int argc, char** argv )
{
  char timebuf[256];
  time_t oldtime = time(0);
  while( 1 ) {
    strftime(timebuf, sizeof( timebuf ), "%FT%TZ", gmtime( &oldtime ));
    cout << timebuf << endl;
    while( oldtime == time(0) ) {
      usleep( 100000 );
    }
    oldtime = time(0);
  }
  return 0;
}




