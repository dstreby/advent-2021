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

  if ( fp == NULL ) {
    printf ( "Unable to read from file\n" );
    return EXIT_FAILURE;
  }

  // get number of ints in file
  int num = 0;
  int nums = 0;
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
  int windowIncs = 0;
  // stop the loop one element from the end, since the last integer
  // has no subsequent integer to compare to
  for(int i = 0; i < arrLen - 1; i++) {
    if ( depth[i+1] > depth[i]  ) {
      increases++;
    }
    // only evaluate the sliding window until the array iterator
    // is 4 elements from the end of the array so we don't overshoot
    // i.e. at i = arrLen - 4; depth[i+3] is the last element in the array
    if ( i < ( arrLen - 3 ) ) {
      if ( (depth[i+1] + depth[i+2] + depth[i+3]) > (depth[i] + depth[i+1] + depth[i+2]) ) {
        windowIncs++;
      }
    }
  }

  printf ( "%d, %d\n", increases, windowIncs );

  return EXIT_SUCCESS;
}
