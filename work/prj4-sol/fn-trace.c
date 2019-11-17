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

typedef struct FnsData{
	//pointer to the array
	FnInfo * pointer;
	// keep track of size
	size_t size;
	// current index
	int index;
	// number of elements used
	size_t used;
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
  // opcode
  unsigned char op = *(unsigned char *)rootFn;
  while(!is_ret(op)){
	  printf("is_ret_status: %d\n", is_ret(op));
	  // get length of instr
	  int instr_length = get_op_length(rootFn);
	  // print instr_length
	  printf("length: %d\n", instr_length);
	  //go to next instruction (this is wrong - how do you increment?)
	  rootFn = rootFn + 0x4;
	  // update op
	  op += instr_length;

  }
  printf("is_ret_status: %d\n", is_ret(op));
  // create data type
  /*
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
