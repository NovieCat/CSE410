
/******************************************************************************
  Demonstrate the use of "pipe" with "exec"
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int fd[2], pid;

  pipe( fd );

  pid = fork();

  if (pid == 0)
  {
    // Child process:  make the "write" end of the pipe map to "stdout",
    // close both ends of the pipe, then exec "ps"

    dup2( fd[1], STDOUT_FILENO );

    close( fd[0] );
    close( fd[1] );

    execl( "/bin/ps", "ps", "-ef", NULL );
  }
  else
  {
    // Parent process:  make the "read" end of the pipe map to "stdin",
    // close both ends of the pipe, then exec "grep"

    dup2( fd[0], STDIN_FILENO );

    close( fd[0] );
    close( fd[1] );

    execl( "/bin/grep", "grep", "-v", "root", NULL );
  }

  exit( 0 );
}

