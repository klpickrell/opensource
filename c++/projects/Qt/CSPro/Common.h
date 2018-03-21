#ifndef COMMON_H
#define COMMON_H

#include <vector>

class WordElementType
{

public:

    typedef std::vector<unsigned char> wordType;

    wordType wordValue;
    int integerCountReferenced;
};

#endif 


