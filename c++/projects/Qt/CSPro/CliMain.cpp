#include <stdio.h>
#include "CacheAnalysis.h"


int main()
{
   int wi;
   WordElementType word;
   
   CacheAnalysis cacAnal;

   cacAnal.cacheInp.kValue=128;
   cacAnal.cacheInp.mValue=16;
   cacAnal.cacheInp.rValue=128;
   cacAnal.cacheInp.fileName="Trace2.txt";
   cacAnal.cacheInp.fileType="ASCII";

   cacAnal.cacheInp.ParseInput();
   cacAnal.StartAnalysis();
   while (cacAnal.MoreWords())
   {
      printf("%d/%d\n",cacAnal.inpind,cacAnal.cacheInp.words.size());
      cacAnal.ProcessNextWord();
   }


   printf("Cache analysis parameters \n");

   printf("Num Hits : %d \n",cacAnal.cacheOup.countNumHits);
   printf("Num Misses : %d \n",cacAnal.cacheOup.countNumMisses);
   printf("Hit Ratio : %f \n",cacAnal.cacheOup.hitRatio);

   printf("\n\n");
/*
   printf("Input words");
   for (int ind=0;ind < cacAnal.cacheInp.words.size();ind++)
   {
      word=(WordElementType)cacAnal.cacheInp.words.at(ind);
      printf("\nWord ");
      for (wi=0;wi<cacAnal.cacheInp.rValue/8;wi++)
         printf("%x ",word.wordValue[wi]);
   }
*/
   printf("\n\nReference Count of words");

   for (int ind=0;ind < cacAnal.cacheOup.words.size();ind++)
   {
      word=(WordElementType)cacAnal.cacheOup.words.at(ind);
      printf("\nWord ");
      for (wi=0;wi<cacAnal.cacheInp.rValue/8;wi++)
         printf("%x ",word.wordValue[wi]);
      printf("Count %d", word.integerCountReferenced);
   }

}
