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

typedef struct CacheLineImpl{
    MemAddr addr;
    unsigned tag;
    int valid;
    int LRUVal;

}CacheLine;

typedef struct CacheSetImpl{
    CacheLine *lines;
    int numLines;
    unsigned mruHolder;

}CacheSet;

struct CacheSimImpl{
    CacheSet *sets;
    int numSets;
    //CacheParams params;
    unsigned nSetBits;          /** s # of seets is 2** this */
    unsigned nLinesPerSet;      /** E # of cache lines/ set */
    unsigned nLineBits;         /** b # of bytes/line is 2**this */
    unsigned nMemAddrBits;      /** m # of primary mem addr;
                                    total primary addr space is 2**this*/
    Replacement replacement;    /** replacement strategy*/

};


CacheSim *
new_cache_sim(const CacheParams *params)
{
    CacheSim *cache;
    cache = malloc(sizeof(*cache));  
    cache->nSetBits = params->nSetBits;
    cache->nLinesPerSet = params->nLinesPerSet;
    cache->nLineBits = params->nLineBits;
    cache->nMemAddrBits = params->nMemAddrBits;
    cache->replacement = params->replacement;

    //unsigned s = cache-> params.nSetBits;
    //unsigned E = cache-> params.nLinesPerSet;

    cache->numSets = (1 << cache->nSetBits);

    //malloc size of CachSimImpl struct
    cache->sets = malloc((cache->numSets)* (sizeof(*cache->sets)));
    for(int j = 0; j < cache->numSets; ++j){
	cache->sets[j].lines = malloc(cache->nLinesPerSet* (sizeof(*cache->sets->lines)));

    for (int i = 0; i < cache->numSets; ++i)
    {

        for (int j = 0; j < cache->nLinesPerSet; ++j)
        {
	    printf("%d\n", j);
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
    //free all memory used
    free(cache->sets->lines);
    free(cache->sets);
    free(cache);
}


/** Return non-zero iff addr hits cache */
CacheResult
cache_sim_result(CacheSim *cache, MemAddr addr)
{
    CacheResult result  = { CACHE_MISS_WITH_REPLACE, 0x1234 };
    unsigned s = cache->nSetBits;
    unsigned E = cache->nLinesPerSet;
    unsigned b = cache->nLineBits;
    unsigned m = cache->nMemAddrBits;

    Replacement replace = cache->replacement;
    //cache->sets->lines->valid = 0;

    unsigned tagBits = m-(s+b);
    //printf("tagBits: %u", tagBits);

    unsigned tag = addr << (s + b);

    //printf("tag: %u", tag);

    unsigned temp = addr << (tagBits);
    //printf("temp: %u", temp);

    int setIndex = temp >> (tagBits +b);
    //printf("setIndex: %d", setIndex);

    time_t timer;
    srand((unsigned) time(&timer));


    bool validLine = true;
    for (int i = 0; i < E; ++i)
    {
        if(cache->sets[setIndex].lines[i].tag != tag){
            //track if a valid line exists in the set
            if(cache->sets[setIndex].lines[i].valid !=0){
                validLine = false;
            }
            else{
                validLine = true;
                cache->sets[setIndex].lines[i].valid = 1;
            }

        }

        else{
            result.status = CACHE_HIT;
            cache->sets->mruHolder = tag;
            break;
        }

    }

    if(validLine == true){
        for (int i = 0; i < E; ++i)
        {
            if(cache->sets[setIndex].lines[i].valid == 0){
                cache->sets[setIndex].lines[i].tag = tag;
                result.status = CACHE_MISS_WITHOUT_REPLACE;
                cache->sets->mruHolder = tag;
                break;
            }
        }


    }

    else{

        if (replace==LRU_R){ //replacement strategy is LRU

            int i = E - 1;
            cache->sets[setIndex].lines[i].tag = tag;
            result.status = CACHE_MISS_WITH_REPLACE;
            result.replaceAddr = addr;
            //break;
        }

        else if(replace==MRU_R){ //replacement strategy is MRU
            for (int i = 0; i < E; ++i)
            {
                if(cache->sets[setIndex].lines[i].tag ==
                    cache->sets->mruHolder){

                    cache->sets[setIndex].lines[i].tag=tag;
                    result.status = CACHE_MISS_WITH_REPLACE;
                    result.replaceAddr = addr;
                    cache->sets->mruHolder = tag;   
                    //break;
                }
            }
        }
        else{ //replacement strategy is Random

            int i = 0;
            i = rand () % E;
            cache->sets[setIndex].lines[i].tag = tag;
            result.status = CACHE_MISS_WITH_REPLACE;
            result.replaceAddr = addr;
            //break;

       }
    }
	return (CacheResult) { .status = CACHE_N_STATUS, .replaceAddr = 0x0 };
    }
