#include <iostream>
#include <stdlib.h>

#include "boost/pointer.hpp"

using namespace std;

void rinplace( char* strval )
{
  if( !strval ) 
    return;

  int length = strlen( strval );
  char* phead = &strval[0];
  char* ptail = &strval[ length-1 ];
  while( phead < ptail ) {
    char temp = *ptail;
    *ptail = *phead;
    *phead = temp;
    phead++;
    ptail--;
  }
}



int main( int argc, char** argv )
{
  char ticom[] = "ticom";

  return 0;
}


