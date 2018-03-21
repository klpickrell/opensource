#ifndef _CACHE_ANALYSIS_H_
#define _CACHE_ANALYSIS_H_

#include <list>
#include <map>
#include <exception>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "CacheInput.h"
#include "CacheOutput.h"
#include "CacheException.h"

#define MAX_NUM_SETS 66000

typedef struct cacheSimulationRootType
{
  WordElementType cacheSet;
}CacheSimulationRootType;

class CacheAnalysis
{
public:
    
    CacheAnalysis( boost::shared_ptr<CacheInputClass> inputs ) :
        cacheInp( inputs )
    {}

    bool MoreWords();
    void StartAnalysis();
    void ProcessNextWord();
    void PerformCacheAnalysis();
    void PerformTemporalAnalysis();
    static int compare(WordElementType word1, WordElementType word2);

    //    void InsertLFU( std::list<WordElementType> &row );
    void InsertLFU( int );
    //    void InsertLRU( std::list<WordElementType> &row );
    void InsertLRU( int );

    unsigned int GetInd(WordElementType &word);

    int percentComplete() const { 
        int complete = 0;
        if( cacheInp && cacheInp->words.size() ) {
            complete = static_cast<int>(static_cast<float>(inpind)/cacheInp->words.size() * 100.0);
        }
        return complete;
    }

    boost::shared_ptr<CacheOutputClass> output() { return cacheOup; }

    void updateSpeedupFactor() {
        if( cacheOup ) {

            float noncached = cacheOup->countTotal * cacheInp->numberOfCycles;
            float cached = 
                ((cacheInp->numberOfCycles+cacheInp->missPenalty) * (cacheOup->countNumMisses + cacheOup->countCompulsoryMisses)) +
                cacheInp->hitOverhead * cacheOup->countNumHits;

            if( noncached > 0 ) {
                cacheOup->speedup = cached/noncached;
            } else {
                cacheOup->speedup = -1;
            }
        }
    }

private:

    //boost::function<void( std::list<WordElementType> )> replacementPolicy;
    boost::function<void( int )> replacementPolicy;

    unsigned int inpind;
    int numRows;
    boost::shared_ptr<CacheInputClass> cacheInp;
    boost::shared_ptr<CacheOutputClass> cacheOup;

    std::map<WordElementType,int> element_indices;

    //    std::list<WordElementType> cacheMat[MAX_NUM_SETS];

};

#endif
