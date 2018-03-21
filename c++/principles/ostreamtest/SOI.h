#ifndef __SOI_H__
#define __SOI_H__
#include <iostream>
class SOI;

class SOI {
  public:
    SOI();
    virtual ~SOI();
    virtual operator bool () const = 0; // returns true if the SOI is valid    
    virtual bool isValid () const = 0; // returns true if the SOI is valid    
};
#endif
