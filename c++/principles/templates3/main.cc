#include "SpecialThing.h"
#include "Policies.h"

#include <iostream>

using namespace std;

class FunkyOne
{
public:
  string id() const { return "FunkyOne!"; }
};

int main( int argc, char** argv )
{
  SpecialThing< FunkyOne, MyBiter, MyKicker > yobiz( new FunkyOne() );
  SpecialThing< FunkyOne, MyBiter > yobaz( new FunkyOne() );

  cout << "Calling yobiz->kickit" << endl;
  yobiz.kickit();
  cout << "Calling yobiz->biteit" << endl;
  yobiz.biteit();

  cout << "Calling yobiz.kick" << endl;
  yobiz.kick( yobiz.getT() );

  cout << "Calling yobaz->kickit" << endl;
  yobaz.kickit();
  cout << "Calling yobaz->biteit" << endl;
  yobaz.biteit();

  return 0;
}


