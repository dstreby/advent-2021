/*
 * =====================================================================================
 *
 *       Filename:  day2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2021 17:48:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DANIEL STREBY (), daniel@dstreby.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 64

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main( int argc, char *argv[] )
{
  FILE *fp = fopen("input", "r");

  if( fp == NULL ) {
    printf( "Unable to read from file\n" );
    return EXIT_FAILURE;
  }

  int horiz = 0;
  int depth = 0;
  char buffer[BUFF_SIZE];
  int distance;
  int i = 0;
  while( fscanf(fp, "%s%d", buffer, &distance) != EOF ) {
    if( strcmp("forward", buffer) == 0 ) {
      horiz += distance;
    } else if( strcmp("up", buffer) == 0 ) {
      depth -= distance;
    } else if( strcmp("down", buffer) == 0 ) {
      depth += distance;
    } else {
      printf ( "Invalid direction encountered: %s\n", buffer );
      return EXIT_FAILURE;
    }
    ++i;
  }

  fclose(fp);

  printf( "depth: %d, distance: %d\n", depth, horiz );
  printf( "depth * distance: %d\n", depth * horiz );

  return EXIT_SUCCESS;
}
