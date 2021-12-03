/*
 * =====================================================================================
 *
 *       Filename:  day3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/03/2021 10:22:06
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
#include <math.h>

#define BUFF_SIZE 16
#define ASCII_OFFSET 48

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bin_to_dec
 *  Description:  
 * =====================================================================================
 */
int bin_to_dec ( long bin )
{
  int dec = 0;

  for ( int i = 0; bin; i++, bin /= 10) {
    if ( bin % 10 ) {
      dec += pow(2, i);
    }
  }

  return dec;
}

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

  // Array to determine if there are more 1's or 0's for each "bit" position in the
  // input data strings. Once processing is complete, the "bit" value will be negative if
  // there were more 0's in that field, or positive if there were more 1's in that field
  int digits[12] = {0};
  int line = 0;
  char buffer[BUFF_SIZE];
  // Iterate through the file, loading one string at a time into buffer
  while ( fscanf(fp, "%s", buffer) != EOF ) {
    fprintf ( stderr, "Line: %04d, Buffer: %s ", line, buffer );
    char *buffChar = buffer;
    int bit = 0;
    // Iterate through buffer, one character at a time (until NULL terminator)
    // and increment / decrement the digits array for each "bit" position.
    while ( buffChar != NULL && *buffChar != '\0' ) {
      fprintf ( stderr, "%c ", *buffChar );
      if ( *buffChar == 0 + ASCII_OFFSET ) {
        digits[bit]--;
      } else if ( *buffChar == 1 + ASCII_OFFSET ) {
        digits[bit]++;
      }
      ++buffChar;
      ++bit;
    }
    fprintf ( stderr, "\n" );
    line++;
  }
  fclose(fp);

  // Construct the binary string for gamma and epsilon values bitwise
  char gamma[] = "000000000000";
  char epsilon[] = "111111111111";
  for ( int i = 0; i < ( sizeof(digits) / sizeof(int) ); i++ ) {
    if ( digits[i] > 0 ) {
      gamma[i] = '1';
      epsilon[i] = '0';
    }
  }

  // Convert the binary strings to decimal integers
  long gamma_bin = atol(gamma);
  int gamma_dec = bin_to_dec(gamma_bin);
  long epsilon_bin = atol(epsilon);
  int epsilon_dec = bin_to_dec(epsilon_bin);

  printf ( "gamma: %s\nepsilon: %s\n", gamma, epsilon);
  printf ( "gamma: %d\nepsilon: %d\n", gamma_dec, epsilon_dec );
  printf ( "power consumption: %d\n", gamma_dec * epsilon_dec );

  return EXIT_SUCCESS;
}
