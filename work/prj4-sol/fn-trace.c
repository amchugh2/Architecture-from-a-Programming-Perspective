#include "fn-trace.h"
#include "x86-64_lde.h"
#include "memalloc.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  CALL_OP = 0xE8,
  RET_FAR_OP = 0xCB,
  RET_FAR_WITH_POP_OP = 0xCA,
  RET_NEAR_OP = 0xC3,
  RET_NEAR_WITH_POP_OP = 0xC2
};

typedef unsigned char Byte;

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
  return
    op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
    op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}

struct FnsData{
	int size;
	int index;
	FnInfo ** pointer;
};

// Called by new_fns_data
// Purpose: Add info about function represented by addr (called by rootFn) and all functions called directly or indirectly by the function as long as the functions havent been seen earlier.
void fn_trace(void * addr, FnsData *fnsData){
	int exist = 0;
	for(int i = 0; i < fnsData->index; i++){
		if(addr == fnsData->pointer[i]->address){
			fnsData->pointer[i]->nInCalls+=1;
			exist=1;
		}
		if(exist == 1){
			return;
		}
		FnInfo *new = malloc(sizeof(FnInfo));
		new->address = addr;
		new->nInCalls = 1;
		new->nOutCalls = 0;

		fnsData->pointer[fnsData->index] = new;
		fnsData->index++;

		if(fnsData->index >= fnsData->size){
			fnsData->size +=2;
			fnsData->pointer = reallocChk(fnsData->pointer, fnsData->size * sizeof(FnInfo**));
		}

		Byte *start = (Byte *)addr;
		int offset = 0;
		while(true){
			if(is_ret(start[offset])){
				new->length = offset+1;
				return;
			}
			int op_len = get_op_length(start + offset);

			if(is_call(start[offset])){
				new->nOutCalls++;
				void *callAddress = start + offset + 5 + *(int *)&(start[offset+1]);
				fn_trace(callAddress, fnsData);
			}
			offset += op_len;
			}
		}

int get_fn(const void *a, const void* b){
	return (*((FnInfo**)a))->address - (*((FnInfo**)b))->address;
}

/** Return pointer to opaque data structure containing collection of
 *  FnInfo's for functions which are callable directly or indirectly
 *  from the function whose address is rootFn.
 */
const FnsData *
new_fns_data(void *rootFn)
{
  //verify assumption used when decoding call address
  assert(sizeof(int) == 4);
  FnsData *first = malloc(sizeof(FnsData));
  // initialize
  first->size = 2;
  first->index = 0;
  // allocate space
  first->pointer = mallocChk(sizeof(FnInfo*) * first->size);
  // call fn_trace
  fn_trace(rootFn, first);
  // sort
  qsort(first->pointer, first->index, sizeof(FnInfo*), &get_fn);
  // return
  return first;
}
  

/** Free all resources occupied by fnsData. fnsData must have been
*  returned by new_fns_data().  It is not ok to use to fnsData after
 *  this call.
 */
void
free_fns_data(FnsData *fnsData)
{
  //@TODO
  for(int i = 0; i < fnsData->index; i++){
	  free(fnsData->pointer[i]);
  }
  free(fnsData->pointer);
  free(fnsData);
}

/** Iterate over all FnInfo's in fnsData.  Make initial call with NULL
 *  lastFnInfo.  Keep calling with return value as lastFnInfo, until
 *  next_fn_info() returns NULL.  Values must be returned sorted in
 *  increasing order by fnInfoP->address.
 *
 *  Sample iteration:
 *
 *  for (FnInfo *fnInfoP = next_fn_info(fnsData, NULL); fnInfoP != NULL;
 *       fnInfoP = next_fn_info(fnsData, fnInfoP)) {
 *    //body of iteration
 *  }
 *
 */
const FnInfo *
next_fn_info(const FnsData *fnsData, const FnInfo *lastFnInfo)
{
  //@TODO
  // If at last
  if(lastFnInfo == NULL){
	  return fnsData->pointer[0];
  }
  for(int i = 0; i < fnsData->index-1; i++){
	  if(fnsData->pointer[i]->address == lastFnInfo->address)
		  return fnsData->pointer[i+1];
  }
  return NULL;
}
}
