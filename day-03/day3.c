/*
 * =====================================================================================
 *
 *       Filename:  day3_pt2.c
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
#define NUM_BITS 12

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binarray_to_dec
 *  Description:  
 * =====================================================================================
 */
int binarray_to_dec ( int *binArray, int arrayLen )
{
  int decimal = 0;
  for ( int i = 0; i < arrayLen; i++ ) {
    int power = arrayLen - i - 1;
    decimal +=  binArray[i] * pow(2, power);
  }
  return decimal;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  reduce_by_minor
 *  Description:  
 * =====================================================================================
 */
void reduce_by_minor ( int *binArray, int rows, int cols, int reducedRows, int minorBit, int index, int *reduced)
{
  int reducedIndex = 0;
  int reducedArray[reducedRows][cols];
  memset(reducedArray, 0, sizeof(reducedArray[0][0]) * reducedRows * cols);
  for ( int i = 0; i < rows; i++ ) {
    if ( *(binArray + i*cols + index) == minorBit ) {
      for ( int j = 0; j < cols; j++ ) {
        reducedArray[reducedIndex][j] = *(binArray + i*cols + j);
      }
      reducedIndex++;
    }
  }

  index++;

  // Count the number of 1's and 0's in the indexed bit position of the array
  int firstBitCount[2] = { 0, 0 };
  for ( int x = 0; x < reducedRows; x++ ) {
    if ( reducedArray[x][index] == 0 ) {
      firstBitCount[0]++;
    } else if ( reducedArray[x][index] == 1 ) {
      firstBitCount[1]++;
    }
  }

  int nextMinorBit = 0;
  if ( ( firstBitCount[0] + firstBitCount[1] ) == 1 ) {
    int final[cols];
    memset(final, 0, cols*sizeof(final[0]));
    for ( int k = 0; k < reducedRows; k++ ) {
      for ( int l = 0; l < cols; l++ ) {
        final[l] = reducedArray[k][l];
      }
    }
    *reduced = binarray_to_dec(final, cols);
    return;
  } else if ( firstBitCount[0] == firstBitCount[1] ) {
    int final[cols];
    memset(final, 0, cols*sizeof(final[0]));
    for ( int k = 0; k < reducedRows; k++ ) {
      if ( reducedArray[k][index] == 0 ) {
        for ( int l = 0; l < cols; l++ ) {
          final[l] = reducedArray[k][l];
        }
        *reduced = binarray_to_dec(final, cols);
        return;
      }
    }
  } else if ( firstBitCount[0] < firstBitCount[1] ) {
    nextMinorBit = 0;
  } else if ( firstBitCount[1] < firstBitCount[0] ) {
    nextMinorBit = 1;
  }

  reduce_by_minor(reducedArray[0], reducedRows, cols, firstBitCount[nextMinorBit], nextMinorBit, index, reduced);

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  reduce_by_dominant
 *  Description:  
 * =====================================================================================
 */
void reduce_by_dominant ( int *binArray, int rows, int cols, int reducedRows, int domBit, int index, int *reduced)
{
  int reducedIndex = 0;
  int reducedArray[reducedRows][cols];
  memset(reducedArray, 0, sizeof(reducedArray[0][0]) * reducedRows * cols);
  for ( int i = 0; i < rows; i++ ) {
    if ( *(binArray + i*cols + index) == domBit ) {
      for ( int j = 0; j < cols; j++ ) {
        reducedArray[reducedIndex][j] = *(binArray + i*cols + j);
      }
      reducedIndex++;
    }
  }

  index++;

  // Count the number of 1's and 0's in the indexed bit position of the array
  int firstBitCount[2] = { 0, 0 };
  for ( int x = 0; x < reducedRows; x++ ) {
    if ( reducedArray[x][index] == 0 ) {
      firstBitCount[0]++;
    } else if ( reducedArray[x][index] == 1 ) {
      firstBitCount[1]++;
    }
  }

  int dominantBit = 0;
  if ( ( firstBitCount[0] + firstBitCount[1] ) == 1 ) {
    int final[cols];
    memset(final, 0, cols*sizeof(final[0]));
    for ( int k = 0; k < reducedRows; k++ ) {
      for ( int l = 0; l < cols; l++ ) {
        final[l] = reducedArray[k][l];
      }
    }
    *reduced = binarray_to_dec(final, cols);
    return;
  } else if ( firstBitCount[0] == firstBitCount[1] ) {
    int final[cols];
    memset(final, 0, cols*sizeof(final[0]));
    for ( int k = 0; k < reducedRows; k++ ) {
      if ( reducedArray[k][index] == 1 ) {
        for ( int l = 0; l < cols; l++ ) {
          final[l] = reducedArray[k][l];
        }
        *reduced = binarray_to_dec(final, cols);
        return;
      }
    }
  } else if ( firstBitCount[0] > firstBitCount[1] ) {
    dominantBit = 0;
  } else if ( firstBitCount[1] > firstBitCount[0] ) {
    dominantBit = 1;
  }

  reduce_by_dominant(reducedArray[0], reducedRows, cols, firstBitCount[dominantBit], dominantBit, index, reduced);

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

  int bitCount[NUM_BITS][2] = {0};
  int bit = 0;
  int rows = 0;
  char buffer[BUFF_SIZE];
  // Iterate through the file, loading one string at a time into buffer
  while ( fscanf(fp, "%s", buffer) != EOF ) {
    //#DEBUG fprintf ( stderr, "Line: %04d, Buffer: %s ", lines, buffer );
    char *buffChar = buffer;
    bit = 0;
    // Iterate through buffer, one character at a time (until NULL terminator)
    // and increment the bitCount array for each "bit" position / value.
    while ( buffChar != NULL && *buffChar != '\0' ) {
      //#DEBUG fprintf ( stderr, "%c ", *buffChar );
      if ( *buffChar == '0') {
        bitCount[bit][0]++;
      } else if ( *buffChar == '1') {
        bitCount[bit][1]++;
      }
      ++buffChar;
      ++bit;
    }
    //#DEBUG fprintf ( stderr, "\n" );
    rows++;
  }

  // set the file pointer back to the start of the file
  fseek(fp, 0, SEEK_SET);

  // For part2, create a 2D array to hold each "bit" as an int
  // we can reuse buffer and bit from above
  int dataset[rows][NUM_BITS];
  memset(dataset, 0, sizeof(dataset[0][0]) * rows * NUM_BITS);
  int line = 0;

  while ( fscanf(fp, "%s", buffer) != EOF ) {
    char *buffChar = buffer;
    bit = 0;
    // Iterate through buffer, one character at a time (until NULL terminator)
    while ( buffChar != NULL && *buffChar != '\0' ) {
      dataset[line][bit] = *buffChar - '0';
      ++buffChar;
      ++bit;
    }
    line++;
  }

  fclose(fp);

  // Count the number of 1's and 0's in the MSB position of the dataset
  int firstBitCount[2] = { 0, 0 };
  for ( int i = 0; i < rows; i++ ) {
    if ( dataset[i][0] == 0 ) {
      firstBitCount[0]++;
    } else if ( dataset[i][0] == 1 ) {
      firstBitCount[1]++;
    }
  }
  int dominantBit = firstBitCount[0] > firstBitCount[1] ? 0 : 1;
  int minorBit = firstBitCount[0] < firstBitCount[1] ? 0 : 1;

  // Reduce the array based on the "dominant" bit to find oxygen generator reading
  int oxGen = 0;
  reduce_by_dominant(dataset[0], rows, NUM_BITS, firstBitCount[dominantBit], dominantBit, 0, &oxGen);

  // Reduce the array based on the "minor" bit to find CO2 scrubber reading
  int scrubber = 0;
  reduce_by_minor(dataset[0], rows, NUM_BITS, firstBitCount[minorBit], minorBit, 0, &scrubber);

  // Construct the binary array for gamma and epsilon values bitwise
  int gamma[NUM_BITS] = { 0 };
  int epsilon[NUM_BITS] = { 0 };
  for ( int i = 0; i < NUM_BITS; i++ ) {
    if ( bitCount[i][1] > bitCount[i][0] ) {
      gamma[i] = 1;
    } else if ( bitCount[i][0] > bitCount[i][1] ) {
      epsilon[i] = 1;
    }
  }

  // Convert the binary strings to decimal integers
  int gamma_dec = binarray_to_dec(gamma, NUM_BITS);
  int epsilon_dec = binarray_to_dec(epsilon, NUM_BITS);

  printf ( "gamma: %d, epsilon: %d\n", gamma_dec, epsilon_dec );
  printf ( "power consumption: %d\n", gamma_dec * epsilon_dec );
  printf ( "oxygen generator: %d, CO2 scrubber: %d\n", oxGen, scrubber );
  printf ( "life support rating: %d\n", oxGen * scrubber );

  return EXIT_SUCCESS;
}
