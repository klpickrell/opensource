#ifndef SOI__H
#define SOI__H
#include <string>
#include "boost/shared_ptr.hpp"
//public interface for all of the different signal types

class SOI
{
  public:

    SOI() { }

    virtual ~SOI(){}

    //    virtual void update(const SyntaxTree &st, const std::string &headerString) = 0;

    virtual operator bool () const = 0; // returns true if the SOI is valid

    virtual double master_collection_freq_mhz() const = 0;

    virtual double slave_collection_freq_mhz() const = 0;

    virtual double collection_bw_khz() const = 0;

    //    virtual ProcessingEnums::Modulation modulation () const
    //    { return ProcessingEnums::NO_MODULATION; }

    virtual void master_collection_freq_mhz(const double &) = 0;

    virtual void slave_collection_freq_mhz(const double &) = 0;

    virtual void collection_bw_khz(const double &) = 0;

    //    virtual void modulation (const ProcessingEnums::Modulation &) = 0;

  private:


};

#endif
