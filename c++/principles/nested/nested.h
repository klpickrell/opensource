#ifndef NESTED_H
#define NESTED_H

#include <vector>

class handler
{
public:
  template< typename T > class method
  {
  public:
    typedef void (T::*ptr)();

    method( typename T::ptr meth ) :
      _method( meth )
    {
    }

    void operator()()
    {
      return _method();
    }

  private:
    typename T::ptr _method;
  };
};

class testhandler
{
public:
  template< typename T > void add_handler( handler::method<T>::ptr );

  void run_test()

private:

  vector< handler* >;
};

#endif
