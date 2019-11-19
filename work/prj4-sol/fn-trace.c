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
  fnInfo->pointer = &rootFn;
  // how to initialize size, index, used, next_index etc
  // while op is not a return
  while(!is_ret(*op)){
	  // if op is a call
	  if(is_call(*op)){
		  // increment outcall
		 nOutCall++;
		  if(nInCall >= 1){
			  nInCall++;
			  // increase size of fnInfo
			  fnInfo->size += get_op_length(*op);
		  }
		  // if hasn't been seen before
		  if(nInCall == 0){
			  // increment inCall
			  nInCall++;
			 // call fn_trace (aux function created by us) to get data
			 // get address of start fn
			 void * new_func = FnInfo->address;
			  fn_trace(new_func, fnsData);
				  // EVERYTHING BELOW IS OLD

			  }
		  }
		}
	 // get len of instr
	  int instr_length = get_op_length ((void *)op);
	  // when scan terminates: enters accumulated length into the FnInfo at the previously saved index in Fnsdata as well as set NOutcalls to number of call instructions 
  }
/*
  // create data type
  unsigned char * pointer = rootFn;
  struct FnsData * new_FnsData = (struct FnsData *)malloc(sizeof(rootFn));
  if(rootFn == NULL){
	  fprintf(stderr, "Error in entering FnInfo");
  }
*/
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
