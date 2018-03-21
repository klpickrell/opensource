#include "tdtemplate.h"
#include <iostream>

using namespace std;

class Spunky
{
public:
  void doit() const { cout << "Spunky.doit" << endl; }
};

class Funky
{
public:
  void doit() const { cout << "Funky.doit" << endl; }
};

class Widget {
public:
  void doit() const { cout << "Widget.doit" << endl; }
};

int main( int argc, char** argv )
{
  MyTemplate< Spunky > thing( (Spunky()) );;
  thing.doit();

  MyTemplate< Funky > thing2( (Funky()) );
  thing2.doit();

  MyTemp2< Widget > thing3( (Widget()) );
  thing3.doit();

  return 0;
}


