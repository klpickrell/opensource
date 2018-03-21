#include <stdlib.h>
#include <math.h>
#include <QDebug>

#include <boost/bind.hpp>

#include "CacheAnalysis.h"

using namespace std;

std::list<WordElementType> cacheMat[MAX_NUM_SETS];


int CacheAnalysis::compare(WordElementType word1, WordElementType word2)
{
    if( word1.wordValue.empty() || word2.wordValue.empty() ) {
        throw CacheException( "attempt to compare empty words" );
    }

    if( word1.wordValue.size() > word2.wordValue.size() ) {
        return 1;
    } else if( word2.wordValue.size() > word1.wordValue.size() ) {
        return -1;
    } else {
        return memcmp( &word1.wordValue[0], &word2.wordValue[0], word1.wordValue.size() );
    }
}

bool operator<( const WordElementType word1, const WordElementType word2 ) {
    return CacheAnalysis::compare( word1, word2 ) < 0;
}

/*
int CacheAnalysis::compare(WordElementType word1, WordElementType word2)
{
    int ind;
//Inputs inp = cacheInp.getInputs();

    for (ind=0;ind < cacheInp->rValue/8; ind ++)
    {
        if (word1.wordValue[ind] > word2.wordValue[ind])
        {
            return 1;
        }
        else if (word1.wordValue[ind] < word2.wordValue[ind])
        {
            return -1;
        }
    }
    if (cacheInp->rValue%8)
    {
        if (word1.wordValue[ind] > word2.wordValue[ind])
        {
            return 1;
        }
        else if (word1.wordValue[ind] < word2.wordValue[ind])
        {
            return -1;
        }
    }
    return 0;
}
*/

bool CacheAnalysis::MoreWords()
{
    return (inpind < cacheInp->words.size());
}

void CacheAnalysis::StartAnalysis()
{
     inpind=0;
     cacheOup.reset( new CacheOutputClass );
     cacheOup->countTotal=cacheInp->words.size();
     cacheOup->countNumHits=0;
     cacheOup->countNumMisses=0;
     cacheOup->countCompulsoryMisses=0;
     cacheOup->hitRatio=(cacheOup->countNumHits*1.0)/(cacheOup->countTotal);


     if( cacheInp->replacementPolicy == "LFU" ) {
         replacementPolicy = boost::bind( &CacheAnalysis::InsertLFU, this, _1 );
     } else if( cacheInp->replacementPolicy == "LRU" ) {
         replacementPolicy = boost::bind( &CacheAnalysis::InsertLRU, this, _1 );
     } else {
         throw CacheException( string( "Unknown replacement policy " ) + cacheInp->replacementPolicy );
     }

     PerformCacheAnalysis();
     PerformTemporalAnalysis();
     inpind++;
}

void CacheAnalysis::ProcessNextWord()
{
    PerformTemporalAnalysis();
    PerformCacheAnalysis();
    //    cacheOup->hitRatio=(cacheOup->countNumHits*1.0)/(cacheOup->countNumHits+cacheOup->countNumMisses);
    cacheOup->hitRatio=cacheOup->countNumHits/cacheOup->countTotal;
    inpind++;
}

unsigned int CacheAnalysis::GetInd(WordElementType &word)
{
    int ind;
    unsigned int index=0;
    int numKBits=(int)logb(cacheInp->kValue);
    for (ind=0;ind < numKBits/8; ind ++)
    {
        index = (index << 8) | (unsigned char)(word.wordValue[ind]);
    }
    if (numKBits % 8)
    {
        index = (index << (numKBits % 8)) | ((unsigned char)word.wordValue[ind]>> (8 - (numKBits % 8)));
    }
    return index;
}

//void CacheAnalysis::InsertLFU(list<WordElementType> &row)
void CacheAnalysis::InsertLFU(int row_idx)
{
    list<WordElementType>& row = cacheMat[row_idx];

    list<WordElementType>::iterator ind,new_pos;
    WordElementType inpword,oupword;
    inpword=(WordElementType)cacheInp->words.at(inpind);
    if( inpword.wordValue.empty() ) {
        return;
    }

    list<WordElementType>::iterator least_frequent = row.end();
    for (ind=row.begin();ind != row.end(); ind++)
    {
        if( ind->wordValue.empty() ) {
            break;
        }

        if( ind->integerCountReferenced > oupword.integerCountReferenced ) {
            least_frequent = ind;
        }

        oupword=*ind;
        if (compare(oupword,inpword) == 0) {
            //            qDebug( "compare succeeded" );

            oupword.integerCountReferenced++;
            row.erase(ind);
            row.insert(least_frequent,oupword);
            cacheOup->countNumHits++;
            return;
        }
    }

    //    qDebug( (QString("row.size ") + QString::number( (int)row.size() )).toStdString().c_str() );
    if ((int)row.size() >= cacheInp->mValue)
    {

        inpword.integerCountReferenced=1;
        cacheOup->countNumMisses++;
        row.pop_front();
        row.push_back(inpword);

        //        qDebug( (QString("countNumMisses ") + QString::number( cacheOup->countNumMisses)).toStdString().c_str() );
    }
    else
    {
        inpword.integerCountReferenced=1;
        cacheOup->countCompulsoryMisses++;
        row.push_back(inpword);

        //        qDebug( (QString("countCompulsoryMisses ") + QString::number( cacheOup->countCompulsoryMisses)).toStdString().c_str() );
    }
}

//void CacheAnalysis::InsertLRU(list<WordElementType> &row)
void CacheAnalysis::InsertLRU( int idx )
{
    list<WordElementType>& row = cacheMat[ idx ];

    list<WordElementType>::iterator ind;
    WordElementType inpword,oupword;
    inpword=(WordElementType)cacheInp->words.at(inpind);
    if( inpword.wordValue.empty() ) {
        return;
    }

    for( ind=row.begin();ind != row.end(); ind++ )
    {
        if( ind->wordValue.empty() ) {
            break;
        }

       oupword=*ind;
       if (compare(oupword,inpword) == 0)
       {
           //           qDebug( "compare succeeded" );

           row.erase(ind);
           row.push_front(oupword);
           cacheOup->countNumHits++;
           return;
       }
    }
    if ((int)row.size() >= cacheInp->mValue)
    {
        cacheOup->countNumMisses++;
        row.pop_front();
        row.push_back(inpword);
    }
    else
    {
        cacheOup->countCompulsoryMisses++;
        row.push_back(inpword);
    }
}

void CacheAnalysis::PerformCacheAnalysis()
{
   WordElementType inpword;
   int index;
   if (cacheInp->rValue == 0 || 
       cacheInp->kValue == 0)
   {
       //       printf("Error : zero input parameters \n");
   }
   inpword=(WordElementType)cacheInp->words.at(inpind);
   index = GetInd(inpword); 
   //printf("getind done %d %d %d %d \n", cacheInp->kValue,cacheInp->rValue,cacheInp->mValue,index);
   //   fflush(stdout);

   //   replacementPolicy( cacheMat[index] );
   replacementPolicy( index );

   //printf("insertLFU done\n");
   //   fflush(stdout);
   
}

void CacheAnalysis::PerformTemporalAnalysis()
{
    WordElementType inpword,oupword;
    vector<WordElementType>::iterator oupitr,new_pos; 
    //numWords,oupind;
    if (cacheInp->rValue == 0 || 
        cacheInp->kValue == 0)
        {
            //       printf("Error : zero input parameters \n");
        }

   
    // for (inpind =0;inpind < cacheInp.words.size();inpind++)

    inpword=(WordElementType)cacheInp->words.at(inpind);
    if( inpword.wordValue.empty() ) {
        return;
    }

    std::map<WordElementType,int>::iterator index = element_indices.find( inpword );
    if( index != element_indices.end() ) {
        cacheOup->words[index->second].integerCountReferenced++;
    } else {
        inpword.integerCountReferenced=1;
        cacheOup->words.push_back(inpword);
        element_indices.insert( make_pair(inpword, cacheOup->words.size()-1) );
    }
}

