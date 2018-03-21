#ifndef TD
#define TD

template< typename T > class MyTemplate
{
public:  
  MyTemplate( T myt )
  {
    _myt = myt;
  }

private:

  T _myt;

public:

  void doit() const { return _myt.doit(); }
};

#endif
