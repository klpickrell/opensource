#include <memory>
#include <iostream>
#include <stdio.h>
#include "uff2packed.h"

using namespace std;

int main( int argc, char** argv )
{

  char* pool = new char[ sizeof( UFF2_metadata ) + 4 ];
  auto_ptr< UFF2_metadata > p( new( pool ) UFF2_metadata );
  
  p->record_length = 10;
  p->header_length = sizeof( UFF2_metadata ) + 4;
  p->timestamp.ts_sec = 10;
  p->timestamp.ts_nsec = 500;
  sprintf( p->site_id, "h412" );

  cout << "calling p.reset( 0 )" << endl;

  p.reset( 0 );

  cout << "called p.reset( 0 )" << endl;

  return 0;
}


