#include "cache-sim.h"
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

/** Create and return a new cache-simulation structure for a
 *  cache for main memory withe the specified cache parameters params.
 *  No guarantee that *params is valid after this call.
 */

// struct implementation
// for each line
typedef struct CacheLineImpl{
    // address
    MemAddr addr;
    // tag
    unsigned tag;
    // if valid
    int valid;
    // value for LRU
    int LRUVal;
}CacheLine;

// for each set
typedef struct CacheSetImpl{
    CacheLine *lines;
    int numLines;
    unsigned mruHolder;
}CacheSet;

// for entire cache
struct CacheSimImpl{
    CacheSet *sets;
    int numSets;
    //CacheParams params;
    unsigned nSetBits;  	// s       
    unsigned nLinesPerSet;     // E
    unsigned nLineBits;        // b
    unsigned nMemAddrBits;     // m
    Replacement replacement;  // replacement strategy
};


CacheSim *
new_cache_sim(const CacheParams *params)
{
    // initialize
    CacheSim *cache;
    // malloc for cache
    cache = malloc(sizeof(*cache));
    // set initial params
    cache->nSetBits = params->nSetBits;
    cache->nLinesPerSet = params->nLinesPerSet;
    cache->nLineBits = params->nLineBits;
    cache->nMemAddrBits = params->nMemAddrBits;
    cache->replacement = params->replacement;

    // number of sets in the Cache
    cache->numSets = (1 << cache->nSetBits);

    //malloc size of CachSimImpl struct
    cache->sets = malloc((cache->numSets)* (sizeof(*cache->sets)));
    
    // for each set in the Cache
    for(int j = 0; j < cache->numSets; ++j){
	    // malloc
	cache->sets[j].lines = malloc(cache->nLinesPerSet* (sizeof(*cache->sets->lines)));
    // for each set in the cache
    for (int i = 0; i < cache->numSets; ++i)
    {
	    // for each line in the set
        for (int j = 0; j < cache->nLinesPerSet; ++j)
        {
		// set to invalid
            cache->sets[i].lines[j].valid = 0;
        }
    }
	}
 return cache;
}

/** Free all resources used by cache-simulation structure *cache */
void
free_cache_sim(CacheSim *cache)
{
    //free all memory used (ascending order)
    free(cache->sets->lines);
    free(cache->sets);
    free(cache);
}


/** Return non-zero iff addr hits cache */
CacheResult
cache_sim_result(CacheSim *cache, MemAddr addr)
{
    // initialize the result
    CacheResult result  = { CACHE_MISS_WITH_REPLACE, 0x1234 };
    // initialize return vals
    unsigned s = cache->nSetBits;
    unsigned E = cache->nLinesPerSet;
    unsigned b = cache->nLineBits;
    unsigned m = cache->nMemAddrBits;

    Replacement replace = cache->replacement;

    // calculate values of the cache
    // tagbits
    unsigned tagBits = m-(s+b);
    // tag
    unsigned tag = addr << (s + b);

    unsigned temp = addr << (tagBits);
    // index of the set
    int setIndex = temp >> (tagBits +b);

    // get time
    //time_t timer;
    //srand((unsigned) time(&timer));
   
    // initialize bool validline
    bool validLine = true;
    // for each line in the cache set: search for line with same tag
    for (int i = 0; i < E; ++i)
    {
	// if line's tags do not equal each other
        if(cache->sets[setIndex].lines[i].tag != tag){
		// if the line is valid
            if(cache->sets[setIndex].lines[i].valid !=0){
		// change status of validLine
                validLine = false;
            }
            else{ // line is invalid
		// set line to valid
                validLine = true;
                cache->sets[setIndex].lines[i].valid = 1;
            }

        }

        else{ // if the tags do equal each other: cache HIT
	    // change to cacheHIT
            result.status = CACHE_HIT;
	    // change mruHolder to tag
            cache->sets->mruHolder = tag;
            break;
        }

    }
    // if valid line = true 
    if(validLine == true){
	    // for each line in the cache set
        for (int i = 0; i < E; ++i)
        {
	    // go through each line. if line is invalid (MISS)
            if(cache->sets[setIndex].lines[i].valid == 0){
		// change to invalid
                cache->sets[setIndex].lines[i].tag = tag;
		// status is CACHE_MISS_WITHOUT_REPLACE
                result.status = CACHE_MISS_WITHOUT_REPLACE;
                cache->sets->mruHolder = tag;
                break;
            }
        }
    }

    else{ // if cache_miss_with_replace
	// get replacement strategy
	// if least recently used replacement
        if (replace==LRU_R){
	    // go to bottom
            int i = E - 1;
	    // put on bottom
            cache->sets[setIndex].lines[i].tag = tag;
            result.status = CACHE_MISS_WITH_REPLACE;
            result.replaceAddr = addr;
            //break;
        }
	// if most recently used replacement strategy
        else if(replace==MRU_R){
		// for each line in set
            for (int i = 0; i < E; ++i)
            {
		// put on top
                if(cache->sets[setIndex].lines[i].tag ==
                    cache->sets->mruHolder){
                    cache->sets[setIndex].lines[i].tag=tag;
                    result.status = CACHE_MISS_WITH_REPLACE;
                    result.replaceAddr = addr;
                    cache->sets->mruHolder = tag;   
                }
            }
        }
        else{ // random replacement
            int i = 0;
	    // generate random number to determine where to put in cache
            i = rand () % E;
            cache->sets[setIndex].lines[i].tag = tag;
            result.status = CACHE_MISS_WITH_REPLACE;
            result.replaceAddr = addr;
       }
    }
    // return result
	return (CacheResult) { .status = CACHE_N_STATUS, .replaceAddr = 0x0 };
    }
