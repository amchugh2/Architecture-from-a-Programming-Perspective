
#include "big-bits.h"
#include "hex-util.h"
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/** Provide concrete definition for struct BigBits to flesh out
 *  abstract BigBits data type.
 */
struct BigBits {
  //@TODO
  // pointer to the array
  char *c;
  // int that keeps track of size
  int size;
};



/** Return a pointer to a representation of a big integer with value
 *  corresponding to the non-empty hexadecimal string hex.  Note that
 *  hex will only contain hexadecimal characters '0' - '9', 'a' - 'f'
 *  and 'A' - 'F' terminated by a NUL '\0' char.
 *
 *  The string hex may not remain valid after this function returns.
 *
 *  Returns NULL on error with errno set "appropriately".
 */
// TA: get string in, convert to bigBits according to data types, and then return pointer to that bigBit
const BigBits *
newBigBits(const char *hex)
{
  // error checking
  assert(CHAR_BIT == 8);

  //@TODO
  // tret hex as array (pointer)
  // while hex is not ending in null
  // get size of hex
  int size = 0;
  while(hex[size] != '\0'){
	  size++;
  }
  printf("after getting size of array");
  // using size, go through and break into array
  // Big Endian order
  char bigBit[size];
  for(int j = 0; j < size; j++){
	  bigBit[j] = hex[j];
  }
  printf("after breaking into array");
 
 char *pointer = bigBit;
  
  // Make struct object with attributes
  struct BigBits big = {pointer, size};
  BigBits *bigPointer = &big;
  printf("after making pointer");

  printf("Here");
  // return pointer
  return  bigPointer;

  // why is this here
  return NULL;
}

/** Frees all resources used by currently valid bigBits.  bigBits
 *  is not valid after this function returns.
 */

// TA:  free memory on heap and memory
void
freeBigBits(BigBits *bigBits)
{
  //@TODO
  //STACK:
  printf("before freeing anything");
  freeStack(bigBits);
  printf("after freeing stack");
  // HEAP:
  // use malloc (somewhere else) and then call free
  free(bigBits);
  printf("after freeing heap");
}


/** Return a lower-case hex string representing bigBits. Returned
 *  string should not contain any non-significant leading zeros.
 *  Returns NULL on error with errno set "appropriately".  (Note that
 *  there is no call to free the corresponding string).
 */
// TA: return formatted resulting bigBit
const char *
stringBigBits(const BigBits *bigBits)
{
  //@TODO
  printf("before string conversion");
  int i = 0;
  while(bigBits->c[i] == '\0'){
	  i++;
  }
  // updated pointer to bigBits without leading zeros
 return bigBits + i;
 printf("after string conversion");

  return NULL;
}


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  return NULL;
}

/** Return a new BigBits which is the bitwise-| of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
orBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  return NULL;
}

/** Return a new BigBits which is the bitwise-^ of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
xorBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  return NULL;
}