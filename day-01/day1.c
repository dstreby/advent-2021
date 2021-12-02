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

  while ( fscanf(fp, "%d", &num) != EOF ) {
    nums++;
  }

  int foo[nums];
  memset(foo, 0, nums*sizeof(int));

  fseek(fp, 0, SEEK_SET);
  int i = 0;
  while ( fscanf(fp, "%d", &foo[i]) != EOF ) {
    ++i;
  }

  fclose(fp);

  int arrLen = sizeof(foo) / sizeof(foo[0]);
  int bar[arrLen - 1];
  memcpy(bar, foo + 1, sizeof(bar));

  int increases = 0;
  for(int i = 0; i < arrLen - 1; i++) {
    if ( bar[i] > foo[i]  ) {
      increases++;
    }
  }

  printf ( "%d\n", increases );

  return EXIT_SUCCESS;
}
