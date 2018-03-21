#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>


#define FILE_MODE 0644

int main( int argc, char** argv )
{
    
    int fd, i, nloop, zero = 0;
    int* ptr;
    sem_t* mutex;
    if( argc != 3 ) {
        printf( "invalid arguments\n" );
        exit( 0 );
    }
    
    nloop = atoi( argv[2] );

    int mem_size = sizeof( int );


    fd = shm_open( argv[1], O_RDWR | O_CREAT, FILE_MODE );

    if( fd == -1 ) {
        perror( "shm_open failure:" );
        exit( 0 );
    }

    ftruncate( fd, mem_size );

    //    fd = open( argv[1], O_RDWR | O_CREAT, FILE_MODE );
    //    write( fd, &zero, sizeof(int));


    ptr = (int*)mmap( 0, mem_size, PROT_READ|PROT_WRITE, MAP_SHARED,fd,0 );
    close( fd );

    if( ptr == MAP_FAILED ) {
        perror( "mmap failure:" );
        exit( 0 );
    }

    mutex = sem_open( "/wbsemaphore", O_CREAT, FILE_MODE, 1 );
    if( mutex == SEM_FAILED ) {
        perror( "sem_open failure:" );
        munmap( ptr, mem_size );
        exit( 0 );
    }

    sem_post( mutex );

    setbuf( stdout, 0 );
    if( fork() == 0 ) {

        for( i = 0; i < nloop; i++ ) {
            sem_wait( mutex );
            printf( "child: %d\n", (*ptr)++);
            sem_post( mutex );
        }

    } else {

        for( i = 0; i < nloop; i++ ) {
            sem_wait( mutex );
            printf( "parent: %d\n", (*ptr)++);
            sem_post( mutex );
        }
    }


    munmap( ptr, mem_size );
    shm_unlink( argv[1] );

    sem_close( mutex );
    sem_unlink( "/wbsemaphore" );

    return 0;
}


