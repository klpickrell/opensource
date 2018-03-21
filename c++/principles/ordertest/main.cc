#include <stdio.h>

int x=1;

int f( void )
{
    x++;
    return x;
}

int p( int a, int b )
{
    return a+b;
}

int main( int argc, char** argv )
{
    printf( "%d\n", p( x, f() ) );
    return 0;
}


