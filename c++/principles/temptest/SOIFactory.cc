#include "SOIFactory.h"
#include "Signal.h"

SOIFactory::SOIFactory()
{

  register_soi<Signal>();
}

SOIFactory *SOIFactory::instance()
{
  static SOIFactory instance;
  return &instance;
}

boost::shared_ptr<SOI> SOIFactory::construct_SOI(const std::string &headerString)
{
  std::map<std::string, new_soi_func>::iterator
    iter = _identifier_to_soi.begin();

  for( ; iter!= _identifier_to_soi.end(); ++iter )
  {
    std::string value;
    if ( 1 )
    {
      return (*iter->second)( headerString );
    }
  }
  
  return boost::shared_ptr<SOI>( (SOI*)0 );
}

void SOIFactory::identifier_to_soi(const std::string &id, new_soi_func fp)
{
  assert( !_identifier_to_soi.count(id) );
  _identifier_to_soi[ id ] = fp;
}
