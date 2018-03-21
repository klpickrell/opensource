#ifndef POINTER_BANK__H
#define POINTER_BANK__H

/*
  Author: Kris Pickrell
  Date: 12/01/06

  PointerBank: A class to replace server relations.  It keeps a global repository
  of pointers referenced by an id field.  Classes added to the repository must
  implement the id function.  This is intended to provide a common interface when
  storing pointers mapped by a string i.e. Alias, rid, component name, etc.

  Examples:

  set< tmComponent* > tms = PointerBank< tmComponent >::instance()->get( tm_comp_alias ) // gets tmComponent by alias

  set< CollectTask* > cts = PointerBank< CollectTask >::instance()->get( collect_rid ) // gets a task by rid

  tmComponent* tm = PointerBank< tmComponent >::instance()->getfirst(); // get first tmComponent it finds (useful if only one)

*/

#include "singleton.h"

#include <string>
#include <map>
#include <algorithm>
#include <memory>
#include <set>
#include <list>

template< typename T >
class PointerBank : public Tg::singleton< PointerBank<T> >
{
  DECLARE_SINGLETON_FRIENDS( PointerBank<T> );

  typedef std::map< std::string, std::set< T* > > IDPointerMap;

private:
    PointerBank(){}
    ~PointerBank(){}

public:

  void add( T* t ) { 
    using std::set;
    typename IDPointerMap::iterator ip = _pointers.find( t->id() );
    if( ip != _pointers.end() ) {
      set< T* >& v = ip->second;
      v.insert( t );
    } else {
      set< T* > v;
      v.insert( t );
      _pointers.insert( std::make_pair( t->id(), v ) );
    }
  }

  void remove( T* t ) {
    using std::set;
    typename IDPointerMap::iterator ip = _pointers.find( t->id() );
    if( ip != _pointers.end() ) {
      set< T* >& v = ip->second;
      typename set< T* >::iterator iv = v.begin();
      while( iv != v.end() ) {
	if( (*iv) == t ) {
	  v.erase( iv );
	  break;
	}
      }
    } 
  }

  T* getfirst( const std::string& s ) {
    using std::set;

    typename IDPointerMap::iterator ip;
    T* thet = 0;

    ip = _pointers.find( s );

    if( ip != _pointers.end() ) {
      set< T* >& v = ip->second;
      typename set< T* >::iterator iv = v.begin();
      if( iv != v.end() ) {
          thet = (*iv);
      }
    }

    return thet;
  }

  std::list< T* > getall() {

	using std::list;

	list< T* > mylist;

	typename IDPointerMap::iterator ip;

	ip = _pointers.begin();
	while( ip != _pointers.end() ) {
	  mylist.insert( mylist.end(), ip->second.begin(), ip->second.end() );
	  ip++;
	}

	return mylist;
  }


  std::set< T* > get( const std::string& s ) {

    using std::set;
    using std::auto_ptr;

    set< T* > myset;
    typename IDPointerMap::iterator ip;
    ip = _pointers.find( s );

    if( ip != _pointers.end() ) {
      set< T* >& v = ip->second;
      myset.insert( v.begin(), v.end() );
    }

    return myset;
  }

private:

  IDPointerMap _pointers;
};

#endif
