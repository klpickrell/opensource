#ifndef INCLUDED_LINKED_LIST
#define INCLUDED_LINKED_LIST

template< typename T > class linked_list
{
public:
  
  class node
  {
  public:
    node( const T& t ) :
      _tval( t )
    {
      _next = 0;
      _prev = 0;
    }

    friend class linked_list;
    friend class linked_list::iterator;

  private:
    T _tval;
    node* _next;
    node* _prev;
  };
  
public:

  class iterator
  {
  public:
    iterator( node* n ) {
      _node = n;
    }

    iterator operator++( int ) {
      iterator prev( _node );
      _node = _node->_next;

      return prev;
    }

    const T* operator->() const { return &_node->_tval; }
    T* operator->() { return &_node->_tval; }

    const T& operator*() const { return _node->_tval; }
    T& operator*() { return _node->_tval; }
    
    bool end() const { return _node == 0; }

    bool operator!() const { return end(); }

  public:

    bool operator==( const linked_list<T>::iterator& it ) {
      return it._node == _node;
    }

    bool operator!=( const linked_list<T>::iterator& it ) {
      return !(this->operator==( it ));
    }

    node* get_node() { return _node; }

  private:
    node* _node;
  };

public:

  linked_list::linked_list()
  {
    _first_node = 0;
    _last_node = 0;
  }

  linked_list::~linked_list()
  {
    iterator cur = begin();
    while( cur != end() ) {
      cur = erase( cur );
    }
  }

  void linked_list<T>::add( const T& t );
  
  iterator begin() { return iterator( _first_node ); }
  iterator end() { return iterator(0); }

  iterator erase( linked_list<T>::iterator it )
  {
    iterator ret = end();
    if( !it ) {
      return ret;
    }

    iterator cur = begin();
    while( !cur.end() && cur != it ) {
      cur++;
    }

    if( !cur.end() ) {
    
      node* n = cur.get_node();
      node* prev = n->_prev;
      node* next = n->_next;
    
      if( prev ) {
	prev->_next = n->_next;
      }

      if( next ) {
	next->_prev = prev;
      }

      delete n;

      ret = iterator( next );
    }

    return ret;
  }

private:

  node* _first_node;
  node* _last_node;
};

template< typename T > 
void linked_list<T>::add( const T& t )
{
  if( _last_node ) {
    _last_node->_next = new node( t );
    _last_node->_next->_prev = _last_node;
    _last_node = _last_node->_next;
  } else {
    _first_node = new node( t );
    _last_node = _first_node;
  }
}

#endif
