#ifndef myte
#define myte

#include <map>
#include <string>

using std::string;
using std::map;

template< typename T >
class HasAMap
{
public:

  void add( T* t ) {
    _pointers.insert( std::make_pair( t->id(), t ) );
  }

  T* get( const string& str ) {
    T* rval = 0;
    typename map< string, T* >::iterator it = _pointers.find( str );
    if( it != _pointers.end() ) {
      rval = it->second;
    }
    return rval;
  }
  

private:

  map< string, T* > _pointers;
};



#endif
