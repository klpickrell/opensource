#ifndef INCLUDED_TTEST
#define INCLUDED_TTEST

template< typename T > class mytemp
{
public:
  class inner {
  public:
    inner( T t ) : myt( t ){}
    T myt;
  };

  mytemp(){}

  inner doit( T t )
  { 
    return inner( t ); 
  }

};

#endif
