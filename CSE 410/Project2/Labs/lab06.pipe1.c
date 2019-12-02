
/******************************************************************************
  Demonstrate the use of "pipe"
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 64

int main()
{
  int fd[2], pid;

  pipe( fd );

  pid = fork();

  if (pid > 0)
  {
    // Parent process:  close "read" end of pipe, display message,
    // then write message into pipe

    char msg[] = "Hello, world!";

    printf( "ID: %ld  Starting execution\n", (long) getpid() );

    close( fd[0] );

    printf( "ID: %ld  Message: %s\n", (long) getpid(), msg );

    write( fd[1], msg, strlen(msg)+1 );

    close( fd[1] );

    printf( "ID: %ld  Halting execution\n", (long) getpid() );

    exit( 0 );
  }
  else
  {
    // Child process:  close "write " end of pipe, read message
    // from pipe, then display it

    int nbytes;
    char buffer[MAX];

    printf( "ID: %ld  Starting execution\n", (long) getpid() );

    close( fd[1] );

    for (;;)
    {
      nbytes = read( fd[0], buffer, MAX );

      if (nbytes == 0) break;

      printf( "ID: %ld  Message: %s\n", (long) getpid(), buffer );
    }

    close( fd[0] );

    printf( "ID: %ld  Halting execution\n", (long) getpid() );

    exit( 0 );
  }
}

