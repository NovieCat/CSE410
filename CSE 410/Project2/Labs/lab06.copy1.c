
/******************************************************************************
  Demonstrate the use of low-level I/O system calls

  Copy the contents of an input file to an output file using system calls.
******************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 64

int main()
{
  char buffer[BUFFER_SIZE];

  int in_fd;
  char in_name[PATH_MAX];
  int in_bytes;

  int out_fd;
  char out_name[PATH_MAX];


  /***** Artificially produce the file names  *****/

  strcpy( in_name, "/user/cse410/Labs/lab06.data" );

  strcpy( out_name, "lab06.result" );


  /***** Open the input file and the output file *****/

  in_fd = open( in_name, O_RDONLY );

  out_fd = open( out_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR );


  /***** Loop until EOF, copying BUFFER_SIZE bytes at a time *****/

  for (;;)
  {
    in_bytes = read( in_fd, buffer, BUFFER_SIZE );

    if (in_bytes == 0) break;

    write( out_fd, buffer, in_bytes );
  }

  close( in_fd );
  close( out_fd );

  exit( 0 );
}

