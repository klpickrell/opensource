#include <stdio.h>

int main( int argc, char** argv )
{
    char* buf = "howdy";
    char buf2[1024];

    sscanf( buf, "%s", buf2 );

    printf( "%s", buf2 );


  return 0;
}


