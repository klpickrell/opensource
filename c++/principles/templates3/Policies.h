#ifndef BLAH
#define BLAH

#include <iostream>

using namespace std;

template< typename T > 
class MyKicker
{
public:
  void kick( T* t ) { cout << "MyKicker::kick" << endl; cout << t->id() << endl; }
};

template< typename T > 
class MyPlaceKicker
{
public:
  void kick( T* t ) { cout << "MyPlaceKicker::kick" << endl; cout << t->id() << endl; }
};

template< typename T > 
class MyBiter
{
public:
  void bite( T* t ) { cout << "MyBiter::bite" << endl; cout << t->id() << endl; }
};
#endif
