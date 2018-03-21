#include <iterator>
#include "CacheInput.h"
#include "CacheException.h"

using namespace std;

//setinput function
void CacheInputClass::setInputs(string fileNm, string fileTp, int rValue, int kValue, int mValue, int noOfCycles, string rPolicy, float mPenalty, float hOhead, bool oIgnored){
	fileName = fileNm;
	fileType = fileTp;
 	//inputValues.rValue = rValue;
 	this->rValue = rValue;
        //inputValues.kValue = kValue ;
        this->kValue = kValue ;
        //inputValues.mValue = mValue;
        this->mValue = mValue;
        //inputValues.numberOfCycles = noOfCycles;
        numberOfCycles = noOfCycles;
        //inputValues.replacementPolicy = rPolicy;
        replacementPolicy = rPolicy;
        //inputValues.missPenality = mPenality;
        missPenalty = mPenalty;
        //inputValues.hitOverhead = hOhead;
        hitOverhead = hOhead;
        //inputValues.offsetIgnored = oIgnored;
        offsetIgnored = oIgnored;

}


//getinput function returns inpur parameters
//Inputs CacheInputClass:: getInputs(){

//return inputValues;


//}


//constructor for ASCII file Input
ASCIIfile::ASCIIfile(string fName){
	fileName = fName;
        const char *np = name;
        np = fileName.c_str();
	inFile.open(np,ios::binary);

                if(!inFile)
                {
                    throw CacheException("Unable to open data file" );
                }

}

//constructor for BINARY file input
BINfile::BINfile(string fName){

	fileName = fName;
        const char *np = name;
        np = fileName.c_str();
 	pFile= fopen(np,"rb");
	
	if (pFile==NULL){
            throw CacheException( "Unable to open data file" );
	}

}

//Parse input function for the ASCII file
void ASCIIfile::ParseInput()
{
	words.clear();

        istream_iterator<string> start( inFile );
        istream_iterator<string> end;
        vector<string> lines( start, end );
        for( vector<string>::iterator it = lines.begin();
             it != lines.end();
             ++it ) {

            WordElementType element;
            element.integerCountReferenced = 0;
            element.wordValue.resize( it->length() );
            memcpy( &element.wordValue[0], it->c_str(), it->length() );
            words.push_back( element );
        }

        /*
        char line[256];
        while(!inFile.eof()) {

            WordElementType element;
            inFile.getline( line, sizeof( line ) );
            int size = strlen( line );
            element.wordValue.resize( size );
            memcpy(&element.wordValue[0], line, size);
            element.integerCountReferenced =0;
            words.push_back(element);
        }
        */
}
	

//Parse Input function for the binary  
void BINfile::ParseInput(){
	 words.clear();

	fseek(pFile,0,SEEK_END);
	fSize = ftell(pFile);
	rewind (pFile);

        char x[256];
        unsigned int wordSize = rValue;
	while(!feof(pFile))
	{

            WordElementType temp;
            size_t result = fread ( pFile, 1, wordSize,pFile);
            if( !result ) break;

            temp.wordValue.resize( wordSize );
            memcpy(&temp.wordValue[0],x,wordSize);
            temp.integerCountReferenced =0;
            words.push_back(temp);
	}
	
}
/*
int main(){
string filename = "Trace2.txt";
ASCIIfile afile(filename);
afile.ParseInput();

string fileName = "Trace3.bin";
BINfile bfile(fileName);
bfile.ParseInput();

bfile.setInputs(5,5,5,5,"abcd",1.0,1.0,true);
Inputs temp;

temp= bfile.getInputs();

cout<<endl<<"HELLO";
cout<<endl<<temp.rValue<<"   "<<temp.kValue<<endl;
return 0;
}*/
