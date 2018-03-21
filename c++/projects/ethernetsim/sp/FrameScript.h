#ifndef FRAME_SCRIPT__H
#define FRAME_SCRIPT__H

#include <vector>
#include <exception>
#include <fstream>

#include "boost/shared_ptr.hpp"
#include "EthernetFrame.h"

class FileException : public std::exception
{
public:

    FileException( const std::string& wh ) :
        _what( wh )
    {}

    ~FileException() throw(){}

    const char* what() const throw() { return _what.c_str(); }

private:

    std::string _what;
};

class FrameScript
{
public:
    FrameScript( const std::string& filename ) throw( FileException,
                                                      Ethernet::FormatError );

    typedef std::vector< Ethernet::Frame > ListType;
    typedef ListType::iterator iterator;

    iterator begin() { return frames.begin(); }
    iterator end() { return frames.end(); }

private:
    ListType frames;
    std::ifstream file;
};

#endif
