
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
  size_t size = strlen(hex) + 1;
  // can i just get the size of above using sizeof() here
  // use int size = strlen(hex) + 1;

 // using size, go through and break into array
  // Big Endian order
 char * bigBit =  (char *) malloc(size);
 if(bigBit == NULL){
	 fprintf(stderr, "error allocating memory in newBigBits");
	 return NULL;
 }
 for(int j = 0; j <= size; j++){
	  bigBit[j] = hex[j];
  }
 char *pointer = bigBit;
  // Make struct object with attributes
  // any memory that you use inside a function disappears when the function is done
 // size of struct: fixed -> only consists of a pointer to a char array and an int
 // 8 bytes + 4 bytes = 12 bytes
  struct BigBits * big  = (struct BigBits *) malloc(sizeof(*big));
 if(big == NULL){
	 fprintf(stderr, "error allocating memory in newBigBits");
	 return NULL;
 }
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
  // HEAP:
 // free(bigBits->c);
  free(bigBits);
}


/** Return a lower-case hex string representing bigBits. Returned
 *  string should not contain any non-significant leading zeros.
 *  Returns NULL on error with errno set "appropriately".  (Note that
 *  th:c
 */
// TA: return formatted resulting bigBit
const char *
stringBigBits(const BigBits *bigBits)
{
  //@TODO
  /*
  int i = 0;
  while(bigBits->c[i] == '0' || bigBits->c[i] == 'x'){
	  i++;
  }
  
 // updated pointer to bigBits without leading zeros
 const char* new = calloc(1, sizeof(bigBits->c));
 new = &(bigBits->c[i]);

 return new;
 */
 size_t len = strlen(bigBits->c);
 char *val = malloc(len+1);
 if(val == NULL){
	 fprintf(stderr, "error allocating memory in stringBigBits");
	 return NULL;
 }
 for(int x =0; x <=len; x++){
	 val[x] = bigBits->c[x];
 }

 int numZeroes = 0;
 for(int x = 0; x <=len; x++){
	 if(x == len && val[x] == '0'){
		 break;
	 }
	 if(val[x] == '0'){
		 numZeroes=numZeroes+1;
	 }
	 else{
		 break;
	 }
 }
 int newLen = len - numZeroes;
 char *retVal = malloc(newLen);
 if(retVal == NULL){
	 fprintf(stderr, "error allocating memory in stringBigBits");
	 return NULL;
 }
 for(int i = 0; i < newLen; i++){
	 retVal[i] = val[i+numZeroes];
 }
 return retVal;
}


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  // steps:
  //  determine shorter operand & create a bigBit of that length
  // malloc for returnBigBits
  //  iterate through each array and & each element to eachother
  // create pointer to returnBigBits
 
  // get size of shorter array
  /*
  int returnSize = bigBits1->size;
  if(bigBits2->size < returnSize) returnSize = bigBits2->size;
  // malloc for returnBigBits
  struct BigBits * returnBigBits = (struct BigBits *) calloc(1, sizeof(*returnBigBits));
  // declare an array equal to returnSize (make sure to set = returnBigBits.c
 // char returnArray[returnSize];
  returnBigBits->c = (char *) calloc(returnSize, sizeof(char));
 // returnBigBits->c = returnArray;

  // iterate through each array and change to numbers to and to eachother
  for(int i = 0; i < returnSize; i++){
	bigBits1->c[i] =  ifChar(bigBits1->c[i]);
  }
  for(int j = 0; j < returnSize; j++){
	  bigBits2->c[j] = ifChar(bigBits2->c[j]);
  }
  // go through each array and & each one to eachother
  for(int k = 0; k < returnSize; k++){
	  returnBigBits->c[k] = bigBits1->c[k] & bigBits2->c[k];
  }
  // convert all the numbers back to characters
  for(int t = 0; t < returnSize; t++){
	  returnBigBits->c[t] = ifNum(returnBigBits->c[t]);
  }
  // set returnBigBits to returnSize
  returnBigBits->size = returnSize;
  return returnBigBits;
  */
 const char *bigB1 = stringBigBits(bigBits1);
 const char *bigB2 = stringBigBits(bigBits2);

 size_t strLen1 = strlen(bigB1);
 size_t strLen2 = strlen(bigB2);

 if(strLen1>strLen2){
	int arr[strLen2];
       	for(int x = strLen2-1; x >=0; x--){
		int lenDiff = strLen1- strLen2;
 		int first = ifChar(bigB1[x]);
		int second = ifChar(bigB2[x+lenDiff]);
		arr[x] = first & second;
       }
	char * hexValues = (char *) malloc(strLen2 + 1);
	if(hexValues == NULL){
	 fprintf(stderr, "error allocating memory in andBigBits");
	 return NULL;
 }
	for(int x = 0; x < strLen2; x++){
		hexValues[x] = ifNum(arr[x]);
	}
	char *pointer = hexValues;
	struct BigBits * big = (struct BigBits *)malloc(sizeof(*big));
	if(big == NULL){
	 fprintf(stderr, "error allocating memory in andBigBits");
	 return NULL;
 }
	big -> size = strLen2 + 1;
	big -> c = pointer;
	return big;
	       
}
else{
	int arr[strLen1];
	for(int x = strLen1-1;x>= 0; x--){
		//int lenDiff = strLen2 - strLen1;
		int first = ifChar(bigB1[x]);
		int second = ifChar(bigB2[x]);
		arr[x] = first & second;
	}
	char * hexValues = (char *)malloc(strLen1+1);
	if(hexValues == NULL){
	 fprintf(stderr, "error allocating memory in andBigBits");
	 return NULL;
 }
	for(int x = 0; x<strLen1; x++){
		hexValues[x] = ifNum(arr[x]);
	}
	char * pointer = hexValues;
	struct BigBits * big = (struct BigBits *)malloc(sizeof(*big));
	if(big== NULL){
	 fprintf(stderr, "error allocating memory in andBigBits");
	 return NULL;
 }
	big -> size = strLen2 + 1;
	big -> c = pointer;
	return big;
}
return NULL;
}


int ifChar(char c){
	// check type 
	if(c >= '0' && c <= '9'){
		return c - '0';
	}
	// check letter and return appropriate integer
	else if (c == 'a' || c == 'A'){
		return 10;
	}
	else if (c == 'b' || c == 'B'){
		return 11;
	}
	else if (c == 'c' || c == 'C'){
		return 12;
	}
	else if (c == 'd' || c == 'D'){
		return 13;
	}
	else if (c == 'e' || c == 'E'){
		return 14;
	}
	else{ //(if c == 'f'){
		return 15;
	}
}

char ifNum(int i){
	// check type 
	if(i >= 0 && i <= 9){
		return i + '0';
	}
	// check letter and return appropriate integer
	else if (i == 10){
		return 'a';
	}
	else if (i == 11){
		return 'b';
	}
	else if (i == 12){
		return 'c';
	}
	else if (i == 13){
		return 'd';
	}
	else if (i == 14){
		return 'e';
	}
	else{// if (i == 15){
		return 'f';
	}
}



/** Return a new BigBits which is the bitwise-| of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
orBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  //steps:
  // 1. determine LONGER operand and create bigBit of that lenght
  // 2. malloc for pointer and struct
  // find out shorter array and | with zeroes to equal length of other ar	ray
  // 3. iterate through each array and | each element to eachotehr
  // 4. translate back to numb
  
  _Bool isLarger = bigBits1->size > bigBits2->size;
  int returnSize = bigBits2->size;
  int shorterSize = bigBits1->size;
  if(isLarger){
 	returnSize = bigBits1->size;
       	shorterSize = bigBits2->size;
  }

  //malloc for return val
  struct BigBits * returnBigBits = (struct BigBits *) malloc(sizeof(*returnBigBits));
  if(returnBigBits == NULL){
	 fprintf(stderr, "error");
	return NULL;
  }

  // malloc for returnBigBits->c
  returnBigBits->c = (char *) malloc(returnSize);
  // find out length of shorter array
  for(int i = 0; i < returnSize; i++){
	  bigBits1->c[i] = ifChar(bigBits1->c[i]);
  }
  for(int j = 0; j < returnSize; j++){
	  bigBits2->c[j] = ifChar(bigBits2->c[j]);
  }
  // go through all the filled-in numbers and or them
  if(isLarger){
	  for(int k = 0; k < (returnSize - shorterSize); k++){
		  returnBigBits->c[k] = bigBits1->c[k] | 0;
	  }
	  for(int a = 0; a < returnSize; a++){
		  returnBigBits->c[a + (returnSize - shorterSize)] = bigBits1->c[a +(returnSize - shorterSize)] | bigBits2->c[a];
  }
  }
  else if(!isLarger){
	  for(int h = 0; h < (returnSize - shorterSize); h++){
		  returnBigBits->c[h] = bigBits2->c[h] | 0;
	  }
	  for(int g = 0; g < returnSize; g++){
		  returnBigBits->c[g + (returnSize - shorterSize)] = bigBits2->c[g + (returnSize - shorterSize)] | bigBits1->c[g];
  }
  }
  for(int n = 0; n < returnSize; n++){
	  returnBigBits->c[n] = ifNum(returnBigBits->c[n]);
  }
  returnBigBits->size = returnSize;
  return returnBigBits;

}

/** Return a new BigBits which is the bitwise-^ of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
xorBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
   _Bool isLarger = bigBits1->size > bigBits2->size;
  int returnSize = bigBits2->size;
  int shorterSize = bigBits1->size;
  if(isLarger){
 	returnSize = bigBits1->size;
       	shorterSize = bigBits2->size;
  }

  //malloc for return val
  struct BigBits * returnBigBits = (struct BigBits *) calloc(1, sizeof(*returnBigBits));
  // malloc for returnBigBits->c
  returnBigBits->c = (char *) calloc(returnSize, sizeof(char));
 if(returnBigBits == NULL){
	 fprintf(stderr, "error");
	return NULL;
  }
  // find out length of shorter array
  for(int i = 0; i < returnSize; i++){
	  bigBits1->c[i] = ifChar(bigBits1->c[i]);
  }
  for(int j = 0; j < returnSize; j++){
	  bigBits2->c[j] = ifChar(bigBits2->c[j]);
  }
  // go through all the filled-in numbers and or them
  if(isLarger){
	  for(int k = 0; k < (returnSize - shorterSize); k++){
		  returnBigBits->c[k] = bigBits1->c[k] ^ 0;
	  }
	  for(int a = 0; a < returnSize; a++){
		  returnBigBits->c[a + (returnSize - shorterSize)] = bigBits1->c[a +(returnSize - shorterSize)] ^ bigBits2->c[a];
  }
  }
	else if(!isLarger){
		  for(int h = 0; h < (returnSize - shorterSize); h++){
			  returnBigBits->c[h] = bigBits2->c[h] ^ 0;
	  }
		  for(int g = 0; g < returnSize; g++){
			  returnBigBits->c[g + (returnSize - shorterSize)] = bigBits2->c[g + (returnSize - shorterSize)] ^ bigBits1->c[g];
  	}
  	}
  for(int n = 0; n < returnSize; n++){
	  returnBigBits->c[n] = ifNum(returnBigBits->c[n]);
  }
  returnBigBits->size = returnSize;
  return returnBigBits;


}
