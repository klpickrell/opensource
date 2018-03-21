#include "slog_stream.h"
#include <iostream>

using namespace std;


// ===========================================================================
// slog_streambuf
// ===========================================================================

template <class CharT, class Traits, class Alloc>
slog_streambuf<CharT, Traits, Alloc>::
slog_streambuf ()
{
  _buffer.reserve( 512 );
}


template <class CharT, class Traits, class Alloc>
typename slog_streambuf<CharT, Traits, Alloc>::int_type
slog_streambuf<CharT, Traits, Alloc>::
overflow ( int_type c )
{
  if ( traits_type::eq( '\n', c ) ) {
    if ( _buffer.size() ) {
        cout << _level << ", " << _file << ":" << _line << ", " << _func << "<" << _buffer << ">" << endl;
        _buffer.assign( "" );
        _buffer.reserve( 512 );
    }
  } else {
    _buffer.push_back( c );
  }

  return c;
}




// ===========================================================================
// basic_slog_stream
// ===========================================================================

template <class CharT, class Traits, class Alloc>
basic_slog_stream<CharT, Traits, Alloc>::
basic_slog_stream ()
{
}


template class basic_streambuf<char, char_traits<char> >;

template class slog_streambuf<char, char_traits<char>, allocator<char> >;

template class basic_ostream<char, char_traits<char> >;

template class basic_slog_stream<char, char_traits<char>, allocator<char> >;

template class basic_string<char, char_traits<char>, allocator<char> >;

template class basic_ios<char, char_traits<char> >;

void 
std::ios_base::_M_call_callbacks(event __e) throw()
{
  _Callback_list* __p = _M_callbacks;
  while (__p)
    {
  try 
    { (*__p->_M_fn) (__e, *this, __p->_M_index); } 
  catch (...) 
    { }
  __p = __p->_M_next;
    }
}

void 
std::ios_base::_M_dispose_callbacks(void)
{
  _Callback_list* __p = _M_callbacks;
  while (__p && __p->_M_remove_reference() == 0)
    {
  _Callback_list* __next = __p->_M_next;
  delete __p;
  __p = __next;
    }
  _M_callbacks = 0;
}
