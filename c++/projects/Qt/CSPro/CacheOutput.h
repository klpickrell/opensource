#ifndef _CACHE_OUTPUT_H_
#define _CACHE_OUTPUT_H_

#include <vector>
#include "Common.h"


class CacheOutputClass
{
public:
    int countTotal;
    int countNumHits;
    int countNumMisses;
    int countCompulsoryMisses;
    float hitRatio;
    float speedup;
    std::vector<WordElementType> words;
    void PrintOutput();
};

#endif 

