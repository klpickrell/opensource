#include "Signal.h"
#include <sstream>
using namespace std;
Signal::Signal()
{
}

Signal::~Signal()
{
}

//Signal::operator bool () const
//{
//  return true;
//}

ostream& operator << ( ostream& os, const SOI& s )
{
  ostringstream output;
  output<<"operator <<";
  return os<<output.str();
}

ostream& operator << ( ostream& os, const Signal& s )
{
  ostringstream output;
  output<<"operator << (for Signal)";
  return os<<output.str();
}
