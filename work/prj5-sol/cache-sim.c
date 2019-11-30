#include "cache-sim.h"

#include "memalloc.h"
#include <time.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct CacheLine{
	// Track address
	MemAddr addr;
	// Tag
	unsigned tag;
	// If line is valid
	int valid;
	// Track
	int LRU_val;
}CacheLine;

typedef struct CacheSet{
	CacheLine *lines;
	int numLines;
	unsigned mruHolder;
}CacheSet;

struct CacheSimImpl{
	CacheSet *sets;
	int numSets;
	unsigned nSetBits;
	unsigned nLinesPerSet;
	unsigned nLineBits;
	unsigned nAddrBits;
	Replacement replacement;
}CacheSimImpl;

/** Create and return a new cache-simulation structure for a
 *  cache for main memory withe the specified cache parameters params.
 *  No guarantee that *params is valid after this call.
 */
CacheSim *
new_cache_sim(const CacheParams *params)
{
 //@TODO
  // Create cache
  CacheSim *cache;
  cache = malloc(sizeof(*cache));
  cache->nSetBits = params->nSetBits;
  cache->nLinesPerSet = params->nLinesPerSet;
  cache->nLineBits = params->nLineBits;
  cache->nAddrBits = params->nMemAddrBits;
  cache->replacement = params->replacement;

  cache->numSets = ( 1 << cache->nSetBits);

  //memory allocation
  for(int j = 0; j < cache->numSets; ++j){
	cache->sets[j].lines = malloc(cache->nLinesPerSet* (sizeof(*cache->sets->lines)));
  }

  for(int i = 0; i < cache->nLinesPerSet; ++i){
	  for(int j = 0; j < cache->nLinesPerSet; ++j){
		  cache->sets[i].lines[j].valid = 0;
	  }
  }
  return cache;
}

/** Free all resources used by cache-simulation structure *cache */
void
free_cache_sim(CacheSim *cache)
{
  //@TODO
  free(cache->sets->lines);
  free(cache->sets);
  free(cache);
}

/** Return result for addr requested from cache */
CacheResult
cache_sim_result(CacheSim *cache, MemAddr addr)
{
  //@TODO
  CacheResult result = { CACHE_MISS_WITH_REPLACE, 0x1234};
  unsigned s = cache->nSetBits;
  unsigned E = cache->nLinesPerSet;
  unsigned b = cache->nLineBits;
  unsigned m = cache->nAddrBits;

  Replacement replace = cache->replacement;
  unsigned tagBits = m-(s+b);
  unsigned tag = addr << (s+b);
  
  unsigned temp = addr << (tagBits);
  
  int setIndex = temp >> (tagBits + b);

  time_t timer;
  srand((unsigned) time(&timer));

  bool valid_line = true;
  for(int i = 0; i < E; ++i){
	  if(cache->sets[setIndex].lines[i].tag !=tag){
		  // track if valid line exits
		  if(cache->sets[setIndex].lines[i].valid != 0){
			  valid_line = false;
		  }
		  else{
			  valid_line = true;
			  cache->sets[setIndex].lines[i].valid = 1;
		  }
	  }
	  else{
		  result.status = CACHE_HIT;
		  cache->sets->mruHolder = tag;
		  break;
	  }
	  
	  if(valid_line == true){
		  for(int i = 0; i < E; ++i){
			  if(cache->sets[setIndex].lines[i].valid == 0){
				  cache->sets[setIndex].lines[i].tag = tag;
				  result.status = CACHE_MISS_WITHOUT_REPLACE;
				  cache->sets->mruHolder=tag;
				  break;
			  }
		  }
	  }
	  else{
		  if(replace==LRU_R){
			  for(int i = 0; i < E; ++i){
				  if(cache->sets[setIndex].lines[i].tag == cache->sets->mruHolder){
					  cache->sets[setIndex].lines[i].tag = tag;
					  result.status = CACHE_MISS_WITH_REPLACE;
					  result.replaceAddr = addr;
					  cache->sets->mruHolder = tag;
				  }
			  }
		  }
		  else if(replace==MRU_R){
			  for(int i = 0; i < E; ++i){
				  if(cache->sets[setIndex].lines[i].tag == cache->sets->mruHolder){
					  cache->sets[setIndex].lines[i].tag = tag;
					  result.status = CACHE_MISS_WITH_REPLACE;
					  result.replaceAddr = addr;
					  cache->sets->mruHolder=tag;
				  }
			  }
		  }
		  else{
			  int i = 0;
			  i = rand () % E;
			  cache->sets[setIndex].lines[i].tag = tag;
			  result.status = CACHE_MISS_WITH_REPLACE;
			  result.replaceAddr = addr;
		  }
	  }
	 return (CacheResult) { .status = CACHE_N_STATUS, .replaceAddr = 0x0 };
 }
}
