
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main( int argc, char *argv[] )
{
  struct stat stat_buffer;

  stat( argv[1], &stat_buffer );

  printf( "Name: %s\n", argv[1] );
  printf( "Size: %d\n", (int) stat_buffer.st_size );

  return 0;
}


