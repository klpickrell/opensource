#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include "SOI.h"
class Signal;

std::ostream& operator << ( std::ostream& os, const SOI& s );
std::ostream& operator << ( std::ostream& os, const Signal& s );

class Signal:public SOI
{
  public:
    Signal();
    ~Signal();
    virtual operator bool () const { return true; }
    virtual bool isValid() const { return true; }
    friend std::ostream& ::operator << ( std::ostream& os, const Signal& p );

};

#endif 

