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

  int original[nums];
  memset(original, 0, nums*sizeof(int));

  // set the file pointer back to the start of the file
  fseek(fp, 0, SEEK_SET);

  int i = 0;
  while ( fscanf(fp, "%d", &original[i]) != EOF ) {
    ++i;
  }

  fclose(fp);

  int arrLen = sizeof(original) / sizeof(original[0]);
  int shifted[arrLen - 1];

  // create left shifted copy of input array
  memcpy(shifted, original + 1, sizeof(shifted));

  int increases = 0;
  for(int i = 0; i < arrLen - 1; i++) {
    if ( shifted[i] > original[i]  ) {
      increases++;
    }
  }

  printf ( "%d\n", increases );

  return EXIT_SUCCESS;
}
