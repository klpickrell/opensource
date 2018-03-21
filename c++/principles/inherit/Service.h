#ifndef INCLUDED_SERVICE_H
#define INCLUDED_SERVICE_H

#include <vector>
#include <memory>
#include <string>

namespace Services {

  class ServiceConfig {
  public:

    virtual ~ServiceConfig(){}
    virtual void reset() = 0;
  };

  class ServiceInterface {
  public:

    ServiceInterface( const std::string& newid ) : id( si_id ) {}
    ServiceInterface( const ServiceInterface& si ) : id( si._id ) {}

    std::string id() const { return _id; }
    void setId( const std::string& newid ) { _id = newid; }

  private:

    std::string _id;
  };

  class Service {
  public:
	
    Service(){}
    Service( const ServiceInterface& si,
	     const ServiceConfig&    sc )
    {
      setInterface( si );
      setConfig( sc );
    }
    
    Service( const Service& service ) :
    {
      _config.reset( new Service( *(service.getInterface()),
				  *(service.getConfig()) ) );
    }

    virtual ~Service() {}

  public:

    virtual void reset();
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void setConfig( const ServiceConfig& sc ) {
      _config.reset( new ServiceConfig( sc ) );
    }

    ServiceConfig* getConfig() {
      return _config.get();
    }

    virtual void setInterface( const ServiceInterface& si ) {
      _interface.reset( new ServiceInterface( si ) );
    }

    ServiceInterface* getInterface() {
      return _interface.get();
    }

  protected:

    std::auto_ptr< ServiceConfiguration > _config;
    std::auto_ptr< ServiceInterface > _interface;
  };

  typedef std::vector< Service > ServiceList;
  typedef std::vector< Service >::iterator ServiceListIterator;
  typedef std::vector< Service >::const_iterator ServiceListConstIterator;

  class CompositeService {

  public:

    void addService( const Service& ) {
      _services.push_back( 

  protected:

    ServiceList _services;
  };

}

#endif
