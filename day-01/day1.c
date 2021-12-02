/*
 * =====================================================================================
 *
 *       Filename:  day1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2021 10:40:50
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
  FILE *fp = fopen("input", "r");

  int num = 0;
  int nums = 0;
  if ( fp == NULL ) {
    printf ( "Unable to read from file\n" );
    return EXIT_FAILURE;
  }

  // get number of ints in file
  while ( fscanf(fp, "%d", &num) != EOF ) {
    nums++;
  }

  // initialize array
  int depth[nums];
  memset(depth, 0, nums*sizeof(int));

  // set the file pointer back to the start of the file
  fseek(fp, 0, SEEK_SET);

  // load ints from file into array
  int i = 0;
  while ( fscanf(fp, "%d", &depth[i]) != EOF ) {
    ++i;
  }

  fclose(fp);

  // iterate through array and count occurances of n+1>n
  int arrLen = sizeof(depth) / sizeof(depth[0]);
  int increases = 0;
  for(int i = 1; i < arrLen; i++) {
    if ( depth[i+1] > depth[i]  ) {
      increases++;
    }
  }

  printf ( "%d\n", increases );

  return EXIT_SUCCESS;
}
