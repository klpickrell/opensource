#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void* thread_func( void* args );

int global = 0;

int main( int argc, char** argv )
{
  pthread_t thread_id;
  int ret = pthread_create( &thread_id,
			    0,
			    thread_func,
			    0 );
  while( 1 ) {
      cout << global << endl;
  }

  return 0;
}
void* thread_func( void* args )
{
    while( 1 )
        {
            global++;
            global--;
        }
}


