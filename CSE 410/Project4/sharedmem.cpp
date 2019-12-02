#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

// to build: gcc -g -lpthread sharedmem.cpp

/////////////////////////////////////////////////////////////////////////////
//
//	sharedmem.cpp
//
//	Sample code demonstrating use of shared memory and semaphores
//
/////////////////////////////////////////////////////////////////////////////

int main()
{
	int	ShMemId = 0;
	int	retVal = 0;
	char *	ShMemAddr = NULL;
	char 	Buffer[64];
	sem_t *	semPrepare;
	sem_t *	semEat;
	

	// initialize and open the named semaphores
	semPrepare = sem_open("semProduce", O_CREAT | O_EXCL, 0644, 1);
	semEat = sem_open( "semConsume", O_CREAT | O_EXCL, 0644, 0);

	// allocate a shared memory segment
	ShMemId = shmget(IPC_PRIVATE, 1024, 0660);

	switch( fork() )
	{
		case -1:
			break;

		case 0:		// child
			ShMemAddr = (char*)shmat(ShMemId, NULL, 0);		// attach shared memory
			for( int i = 0; i < 4; i++)
			{	
				sem_wait( semPrepare );				// If meal being eaten, wait...
				printf( "Making a meal\n");
				strcpy( ShMemAddr, "Your meal is served!\n" );
				sem_post( semEat );				// Your meal is ready
			}

			retVal = shmdt( (const void*)ShMemAddr );		// detach shared memory
			break;

		default:	// parent
			
			ShMemAddr = (char*)shmat(ShMemId, NULL, 0);		// attach shared memory

			for( int j = 0; j< 4; j++)
			{
				sem_wait( semEat );				// Wait for meal to be prepared
				printf( "\n==============\n");
				printf( "Hurray it's mealtime!\n");
				
				memset( Buffer, 0, 64 );
				strcpy( Buffer, ShMemAddr );
				printf( "%s", Buffer);
				printf( " That was meal #%d\n", j+1 );
				printf( "==============\n\n\n" );
				sem_post( semPrepare );				// Go prepare another meal...
			}

			retVal = shmdt( (const void*)ShMemAddr );		// detach shared memory
			break;
	}
	// remove named semaphores
	sem_unlink( "semProduce" );
	sem_unlink( "semConsume" );
	// close named semaphores
	sem_close( semPrepare );
	sem_close( semEat );

	return(1);
}
