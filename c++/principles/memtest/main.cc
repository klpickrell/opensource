#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main( int argc, char** argv )
{
  
  char chararray[11];
  printf( "chararray is at address: 0x%x\n", chararray );
  for( int i = 0; i < sizeof( chararray ) - 1; i++ ) {
    chararray[i] = i + 'A';
  }

  int idx = 100;
  chararray[ idx ] = 'Q';

  printf( "chararray[ %d ] is at address: 0x%x\n ==>%c\n", idx, &chararray[idx], chararray[idx] );

  cout << (char*)chararray << endl;

  int i = 0;
  while( true ) {
    printf( "writing 'A' to chararray[ %d ] at address: 0x%x\n", i, &chararray[i] );
    chararray[ i ] = 'A';
    printf( "success\n" );
    i++;
  }

  return 100;
}


