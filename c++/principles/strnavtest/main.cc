#include <stdlib.h>
#include <ctype.h>
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{

  char readbuff[1024];
  while( fgets( readbuff, sizeof( readbuff ), stdin ) ) {

    int wordcount = 0;
    char* wordptr = readbuff;
    char prevchar = '\t';
    while( *wordptr != '\n' && *wordptr ) {

      if( isupper( *wordptr ) ) {
	if( isspace( prevchar ) ) {
	  wordcount++;
	}
      }

      prevchar = *wordptr;
      wordptr++;
    }

    cout << "counted " << wordcount << " words" << endl;
  }

  return 0;
}


