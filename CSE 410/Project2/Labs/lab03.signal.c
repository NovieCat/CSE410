
/* Lab Exercise #3 -- UNIX Signals */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler( int signum )
{
  printf( "Processing a SIGINT signal -- exiting.\n" );
  exit( 0 );
}

int main( int argc, char* argv[] )
{
  /* List "handler" as the function to process SIGINT signals */

  signal( SIGINT, handler );

  printf( "\nBeginning execution -- touch CTRL-C to exit the program.\n" );

  /* Loop forever */

  while (1)
  {
    /* do nothing -- wait until user issues interrupt */
  }

  return 0;
}

