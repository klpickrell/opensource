#ifndef MY
#define MY

#include <vector>
#include <boost/iterator/iterator_facade.hpp>
#include <memory.h>


struct Bonk
{
    int length;
    char* thestr;
};

class My 
{
public:

    My( const std::string& str ) {
        
        bonkbuffer.resize( str.size() + sizeof( int ) );
        Bonk* b = reinterpret_cast< Bonk* >( &bonkbuffer[0] );
        b->length = str.size();
        b->thestr = reinterpret_cast< char* >( &bonkbuffer[sizeof(int)] );
        memcpy( b->thestr, str.c_str(), b->length );
    }
    

    Bonk getBonk() {
        Bonk returnval = { bonkbuffer.size() - sizeof(int),
                           reinterpret_cast<char*>(&bonkbuffer[sizeof(int)]) };
        return returnval;
    }

private:
    
    std::vector<char> bonkbuffer;
};


#endif
