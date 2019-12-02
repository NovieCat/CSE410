
/******************************************************************************
  Demonstrate the use of low-level I/O system calls

  Copy the contents of an input file to an output file using system calls.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 64

int main()
{
  char buffer[BUFFER_SIZE];

  int flag;

  int in_fd;
  char in_name[PATH_MAX];
  int in_bytes;

  int out_fd;
  char out_name[PATH_MAX];
  int out_bytes;


  /***** Prompt the user for pathnames *****/

  fprintf( stderr, "\nPlease enter the pathname of the input file: " );

  flag = fscanf( stdin, "%s", &in_name[0] );

  if (flag == EOF) exit( 1 );

  fprintf( stderr, "\nPlease enter the pathname of the output file: " );

  flag = fscanf( stdin, "%s", &out_name[0] );

  if (flag == EOF) exit( 2 );


  /***** Open the input file and the output file *****/

  in_fd = open( in_name, O_RDONLY );

  if (in_fd == -1)
  {
    fprintf( stderr, "\n*** Unable to open '%s' for input\n\n", in_name );

    exit( 3 );
  }

  out_fd = open( out_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR );

  if (out_fd == -1)
  {
    fprintf( stderr, "\n*** Unable to open '%s' for output\n\n", out_name );

    exit( 4 );
  }


  /***** Loop until EOF, copying BUFFER_SIZE bytes at a time *****/

  for (;;)
  {
    in_bytes = read( in_fd, buffer, BUFFER_SIZE );

    if (in_bytes == 0) break;

    if (in_bytes == -1)
    {
      fprintf( stderr, "\n*** Unable to read from '%s'\n\n", in_name );

      exit( 5 );
    }

    out_bytes = write( out_fd, buffer, in_bytes );

    if (out_bytes != in_bytes)
    {
      fprintf( stderr, "\n*** Unable to write to '%s'\n\n", out_name );

      exit( 6 );
    }
  }

  close( in_fd );
  close( out_fd );

  exit( 0 );
}

