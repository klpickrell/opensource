#ifndef CACHE_EXCEPTION__H
#define CACHE_EXCEPTION__H

#include <exception>

class CacheException : public std::exception
{
public:
    CacheException( const std::string& what ) :
        m_what( what ) 
    {}

    ~CacheException() throw() {}
    const char* what() const throw() { return m_what.c_str(); }

private:
    
    std::string m_what;
};

#endif
