
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
  // can i just get the size of above using sizeof() here
  // use int size = strlen(hex) + 1;

  // using size, go through and break into array
  // Big Endian order
  char * bigBit = (char *) malloc(size+1);
  for(int j = 0; j <= size; j++){
	  bigBit[j] = hex[j];
  }
 char *pointer = bigBit;
  // Make struct object with attributes
  // any memory that you use inside a function disappears when the function is done
 // size of struct: fixed -> only consists of a pointer to a char array and an int
 // 8 bytes + 4 bytes = 12 bytes
  struct BigBits * big  = (struct BigBits *) malloc(sizeof(struct BigBits));
  // initializes on the heap
  big->c = pointer;
  big->size = size;
  return  big;
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
  //freeStack(bigBits);
  // HEAP:
  free(bigBits);
  // do i need to free all of the stuff i freed in newBigBits?
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
  int i = 0;
  while(bigBits->c[i] == '0' || bigBits->c[i] == 'x'){
	  i++;
  }
  
 // updated pointer to bigBits without leading zeros
 const char* new_bigBits = &(bigBits->c[i]);
 return new_bigBits;
}


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  // steps:
  // 1. determine shorter operand
  // 2. iterate through array and & each element to eachother
  // 3. create newBigBits (malloc)
  // 4. create pointer to newBigBits
  // can i just bitwise & these two?
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
