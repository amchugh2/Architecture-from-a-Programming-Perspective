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

struct FnsData{
 int size;
 int index;
 FnInfo ** infos;
 };

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
 return
 op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
 op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}
void 
fn_trace(void *addr, FnsData *fnsData)
{
 int exist = 0;
 
 for(int i = 0; i < fnsData->index; i++)
 {
 if(addr == fnsData->infos[i]->address)
	{
	fnsData->infos[i]->nInCalls += 1;
	exist = 1;
	}
 }
 if(exist == 1)
 {
 return;
 }
 
 FnInfo *newInfo = malloc(sizeof(FnInfo));
 newInfo->address = addr;
 newInfo->nInCalls = 1;
 newInfo->nOutCalls= 0;
 
 fnsData->infos[fnsData->index] = newInfo;
 fnsData->index++;

 if(fnsData->index >= fnsData->size)
 {
 fnsData->size += 2;
 fnsData->infos = reallocChk( fnsData->infos, fnsData->size * sizeof(FnInfo**));
 }
 
 Byte *strt = (Byte *)addr;
 int offset = 0;
 
 while(true)
 {
 if(is_ret((strt[offset])))
	{
	newInfo->length = offset+1;
	return;
	}
 // printf("herrr");
 int oplen = get_op_length(strt + offset);
 
 if(is_call(strt[offset]))
	{
	//get address of this func
	newInfo->nOutCalls++;
	// int interval = *((int *)(op+1));
	void *callAddress = strt + offset + 5 + *(int *)&(strt[offset+1]);
	fn_trace(callAddress, fnsData);
 
	}

 offset += oplen;
 
 }
}

/** Return pointer to opaque data structure containing collection of
 * FnInfo's for functions which are callable directly or indirectly
 * from the function whose address is rootFn.
 */
int
fn_thing(const void* info_a, const void* info_b)
{
 return (*((FnInfo**)info_a))->address - (*((FnInfo**)info_b))->address;
}
const FnsData *
new_fns_data(void *rootFn)
{
 //verify assumption used when decoding call address
 assert(sizeof(int) == 4);
 //@TODO
 FnsData *dater = malloc(sizeof(FnsData));
 dater->size = 2;
 dater->index = 0;

 dater->infos = mallocChk(sizeof(FnInfo*) * dater->size);
 
 fn_trace(rootFn, dater);
 qsort(dater->infos, dater->index, sizeof(FnInfo*), &fn_thing);
 
 //this is what we'll return or something like it
 //have to split up the ops in rootFn
 //and then place them into the FnsData 
 return dater;
}

/** Free all resources occupied by fnsData. fnsData must have been
 * returned by new_fns_data(). It is not ok to use to fnsData after
 * this call.
 */
void
free_fns_data(FnsData *fnsData)
{
 //@TODO
 for(int i = 0; i < fnsData->index; i++)
 {
 free((fnsData->infos[i]));
 }
 free(fnsData->infos);
 free(fnsData);
}

/** Iterate over all FnInfo's in fnsData. Make initial call with NULL
 * lastFnInfo. Keep calling with return value as lastFnInfo, until
 * next_fn_info() returns NULL. Values must be returned sorted in
 * increasing order by fnInfoP->address.
 *
 * Sample iteration:
 *
 * for (FnInfo *fnInfoP = next_fn_info(fnsData, NULL); fnInfoP != NULL;
 * fnInfoP = next_fn_info(fnsData, fnInfoP)) {
 * //body of iteration
 * }
 *
 */
const FnInfo *
next_fn_info(const FnsData *fnsData, const FnInfo *lastFnInfo)
{
 //@TODO
 if(lastFnInfo == NULL)
 return fnsData->infos[0];

 for(int i = 0; i < fnsData->index-1; i++)
 {
 if(fnsData->infos[i]->address == lastFnInfo->address)
	return fnsData->infos[i+1];
 }
 return NULL;

 
}
