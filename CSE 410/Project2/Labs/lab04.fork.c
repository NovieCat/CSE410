
/******************************************************************************
  Demonstrate the use of "fork"
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int A = 47;

int main()
{
  int B = 23;

  pid_t pid;

  printf( "\nPID: %4ld  A: %2d  B: %2d\n", (long) getpid(), A, B );

  pid = fork();

  printf( "\nPID: %4ld  A: %2d  B: %2d\n", (long) getpid(), A, B );

  if (pid < 0)
  {
    printf( "\n*** Error: fork failed ***\n" );
    exit( 1 );
  }
  else if (pid == 0)
  {
    A = A + 10;
    B = B + 10;
  }
  else
  {
    A = A + 25;
    B = B + 25;
  }

  printf( "\nPID: %4ld  A: %2d  B: %2d\n", (long) getpid(), A, B );

  exit( 0 );
}

