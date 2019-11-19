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

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
  return
    op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
    op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}

// Called by new_fns_data
// Purpose: Add info about function represented by addr (called by rootFn) and all functions called directly or indirectly by the function as long as the functions havent been seen earlier.
void fn_trace(void * addr, FnsData fnsData){
	FnInfo fnInfo;
	fnInfo->address = &addr;
	fnInfo->nInCalls = 1;
	unsigned char * op = (unsigned char *)addr;
	int func_len = 0;
	while(!is_ret(*op)){
		if(is_call(*op)){
			nOutCalls++;
			int * pointer = op + 0x8;
			pointer+= &(op + 0x4);
			// check if pointer is in fnsData
			if( // POINTER IN FNS DATA){
				nInCalls++
		}
		// not sure about this
		void * new_func = fnInfo ->address;
		fn_trace(new_func, fnsData);
		}
	// Steps
	// Add accumulated length to FnInfo at previously saved index in FnsData
	// Set outCalls to number of call instructions seen during scan of function body (done in while loop)



	



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
  //@TODO
	typedef struct FnsData{
		//array (a collection of FnInfos)
		FnInfo * pointer = NULL;
		// keep track of size
		int size = 0;
		// current index
		int index = 0;
		// number of elements used
		int used = 0;
		// keep track of next index
		int next_index = 0;
	}fnsData;
  // get rootFn to begin, unsigned op to get first step
  unsigned char *op = (unsigned char *)rootFn;
  // initialize first FnsInfo (use malloc here) (maybe do this after fcn - not sure)
  FnInfo fnInfo; // MALLOC?
  fnInfo->address = &rootFn;
  // how to initialize size, index, used, next_index etc
  // while op is not a return
  while(!is_ret(*op)){
	  // if op is a call
	  if(is_call(*op)){
		  nOutCall++;
		  // increment outcall
		  if(nInCall >= 1){
			  nInCall++;
			  // increase size of fnInfo
			  fnInfo->size += get_op_length(*op);
		  }
		  // if hasn't been seen before
		  if(nInCall == 0){
			  // increment inCall and outCall
			  nInCall++;
			 // call fn_trace (aux function created by us) to get data
			 // get address of start fn
			 void * new_func = FnInfo->address;
			 fn_trace(new_func, fnsData);
		  }
		}
          // get len of ins
	 // when scan terminates: enters accumulated length into the FnInfo at the previously saved index in Fnsdata as well as set NOutcalls to number of call instructions 
  }
  return NULL;
}


/** Free all resources occupied by fnsData. fnsData must have been
*  returned by new_fns_data().  It is not ok to use to fnsData after
 *  this call.
 */
void
free_fns_data(FnsData *fnsData)
{
  //@TODO
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
  return NULL;
}
