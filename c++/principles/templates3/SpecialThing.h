#ifndef TEMPLATE_INHERIT_H
#define TEMPLATE_INHERIT_H

#include <iostream>

using namespace std;

template< typename T >
class DefaultKicker
{
public:
  void kick( T* ) { cout << "DefaultKicker::kick" << endl; }
};

template< typename T,
          template <typename GonnaBite> class Biter,
          template <typename GonnaKick> class Kicker = DefaultKicker >

class SpecialThing : public Kicker< T >, public Biter< T >
{
public:

  SpecialThing( T* myt ) :
    _myt( myt )
  {}

  void kickit() { cout << "SpecialThing::kickit" << endl; Kicker<T>::kick( _myt ); }
  void biteit() { cout << "SpecialThing::biteit" << endl; Biter<T>::bite( _myt ); }
  
  T* getT() { return _myt; }

private:
  
  T* _myt;
};

#endif
