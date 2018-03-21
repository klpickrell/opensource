#include <stdio.h>

#ifndef __cplusplus
const char* thestring="not cplusplus";
#else
const char* thestring="cplusplus";
#endif

int main( int argc, char** argv )
{
    printf( "%s\n", thestring );

    return 0;
}


