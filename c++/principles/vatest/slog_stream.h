#ifndef SLOG_STREAM_H
#define SLOG_STREAM_H

#include <ostream>
#include <string>
#include <streambuf>

enum {
	SLOG_EMERG = 0,  /* is unusable                          */
	SLOG_ALERT,      /* action must be taken immediately     */
	SLOG_CRIT,       /* critical conditions                  */
	SLOG_ERR,        /* error conditions                     */
	SLOG_WARNING,    /* warning conditions                   */
	SLOG_NOTICE,     /* normal but significant condition     */
	SLOG_INFO,       /* informational                        */
	SLOG_DEBUG,      /* debug-level messages                 */
	SLOG_NONE,       /* no logging                           */
   SLOG_VERBOSE     /* optional verbose debug messages      */
};

template <class CharT, class Traits, class Alloc>
class slog_streambuf
  : public std::basic_streambuf<CharT, Traits>
{
public:

  typedef CharT                                             char_type;
  typedef Traits                                            traits_type;
  typedef Alloc                                             allocator_type;
  typedef typename traits_type::int_type                    int_type;
  typedef typename traits_type::pos_type                    pos_type;
  typedef typename traits_type::off_type                    off_type;
  typedef typename std::basic_streambuf<CharT, Traits>      base_type;
  typedef typename std::basic_string<CharT, Traits, Alloc>  buffer_type;

  slog_streambuf ();

  void set_info ( const std::string&  file,
                  int                 line,
                  const std::string&  func,
                  int                 level )
  { _file = file; _line = line; _func = func; _level = level; }

protected:
  int_type overflow ( int_type c = traits_type::eof() );


private:
  buffer_type  _buffer;
  std::string  _file;
  std::string  _func;
  int          _line;
  int          _level;
};



template <class CharT, class Traits, class Alloc>
class basic_slog_stream
  : public std::basic_ostream<CharT, Traits>
{
public:
  typedef CharT                                       char_type;
  typedef Traits                                      traits_type;
  typedef Alloc                                       allocator_type;
  typedef typename traits_type::int_type              int_type;
  typedef typename traits_type::pos_type              pos_type;
  typedef typename traits_type::off_type              off_type;
  typedef slog_streambuf<CharT, Traits, Alloc>        streambuf_type;
  typedef std::basic_ostream<char_type, traits_type>  base_type;

  static basic_slog_stream& set_info ( const std::string&  file,
                                       int                 line,
                                       const std::string&  func,
                                       int                 level )
  {
    static bool initialized( false );
    static basic_slog_stream instance;

    if ( !initialized )
    {
      instance.init( &instance._streambuf );
      initialized = true;
    }

    instance._streambuf.set_info( file, line, func, level );
    return instance;
  }

private:
  basic_slog_stream ();

  streambuf_type _streambuf;
};


typedef
  basic_slog_stream<char, std::char_traits<char>, std::allocator<char> >
  slog_stream;



#ifdef SLOG_USE_PRETTY_FUNCTION

#define slog_emerg \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_EMERG  )

#define slog_alert \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_ALERT  )

#define slog_crit \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_CRIT  )

#define slog_err \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_ERR  )

#define slog_warning \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_WARNING  )

#define slog_notice \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_NOTICE  )

#define slog_info \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_INFO  )

#define slog_debug \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_DEBUG  )

#define slog_none \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_NONE  )

#define slog_verbose \
  slog_stream::set_info( __FILE__, __LINE__, __PRETTY_FUNCTION__, SLOG_VERBOSE  )


#else


#define slog_emerg \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_EMERG  )

#define slog_alert \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_ALERT  )

#define slog_crit \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_CRIT  )

#define slog_err \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_ERR  )

#define slog_warning \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_WARNING  )

#define slog_notice \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_NOTICE  )

#define slog_info \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_INFO  )

#define slog_debug \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_DEBUG  )

#define slog_none \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_NONE  )

#define slog_verbose \
  slog_stream::set_info( __FILE__, __LINE__, __FUNCTION__, SLOG_VERBOSE  )


#endif // ifdef SLOG_USE_PRETTY_FUNCTION

#endif // ifndef SLOG_STREAM_H
