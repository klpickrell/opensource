#ifndef CACHE_INPUT__H
#define CACHE_INPUT__H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>

/*struct Inputs{
        int rValue; //word length
        int kValue; //# of Sets
        int mValue; //#of cells
        int numberOfCycles;
        string replacementPolicy;
        float missPenality;
        float hitOverhead;
        bool offsetIgnored;
};*/

class CacheInputClass
{
protected:

//	int rValue; //word length
//      int kValue; //# of Sets
//        int mValue; //#of cells
//        int numberOfCycles;
//        string replacementPolicy;
//        float missPenality;
//        float hitOverhead;
//        bool offsetIgnored;

        std::string fileName;
	std::string fileType;
	int wordSize;
        char name[30];

public :

       int rValue; //word length
        int kValue; //# of Sets
        int mValue; //#of cells
        int numberOfCycles;
        std::string replacementPolicy;
        float missPenalty;
        float hitOverhead;
        bool offsetIgnored;

	//int wordSize;
        std::vector<WordElementType> words;
	
	//constructor, opens file
//	CacheInput(string fName);
	CacheInputClass(){}

	//function  reads the input file and stores the reference words in the vector
	virtual	void ParseInput()=0;	

	//sets the input values
	void setInputs(std::string fileNm, std::string fileTp, int rValue, int kValue, int mValue, int noOfCycles, std::string rPolicy, float mPenalty, float hOhead, bool oIgnored);

	//returns the user inputs
//	Inputs getInputs();

	
	typedef std::vector<WordElementType>::iterator iterator;
	typedef std::vector<WordElementType>::const_iterator const_iterator;

	iterator begin() {return words.begin();}
	iterator end() {return words.end();}

	const_iterator begin() const{return words.begin();}
	const_iterator end() const{return words.end();}






	//destructor closes file
	virtual ~CacheInputClass(){}
	
};

class ASCIIfile:public CacheInputClass{
protected:
        std::ifstream inFile;
	
public:
	//ASCIIfile(string fName):CacheInput(fName){wordSize=WORD_MAX_SIZE;}
	ASCIIfile(std::string fName);
	
	virtual void ParseInput();
	
	virtual ~ASCIIfile(){
	 inFile.close();
	
	//prints the vector for testing
//        for(unsigned int i=0;i<words.size();i++)
 //               {
 //                       temp=words.at(i);
 //                       cout<<temp.wordValue<<endl;
 //               }
        

	}
};

class BINfile:public CacheInputClass{
protected:
	FILE* pFile;
	long fSize;
	char * buffer;
	
public:
	//BINfile(string fName):CacheInput(fName){wordSize=8;}
	BINfile(std::string fName);

	virtual void ParseInput();

	virtual ~BINfile(){
            //            fclose(pFile);
	
	//prints the vector for testing
/*        for(int i=0;i<words.size();i++)
                {
   		printf("\n");
                        temp=words.at(i);
                     //   cout<<temp.wordValue<<endl;
		for(int j=0;j<wordSize/8;j++)
                printf("%c ",temp.wordValue[j]);
		}
  */      

	}
};

#endif
