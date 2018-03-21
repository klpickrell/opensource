#ifndef SIGNAL_H
#define SIGNAL_H

#include "SOI.h"

class Signal;

std::ostream& operator << ( std::ostream& os, const Signal& s );


class Signal
: public SOI
{
  public:
    
    Signal(const std::string &headerString ){}

    virtual ~Signal(){}
    
    virtual void update(const std::string &headerString) { }
    
    virtual operator bool () const { return true; } // returns true if the Signal is valid

    virtual double master_collection_freq_mhz() const { return _collection_freq_mhz; }

    virtual double slave_collection_freq_mhz() const
      { return master_collection_freq_mhz(); }
    
    virtual double collection_bw_khz() const { return _collection_bw_khz; }
      
    virtual double signal_bw_khz() const { return _signal_bw_khz; }
    
    //    virtual ProcessingEnums::Modulation modulation () const { return _modulation; }
    
    virtual void master_collection_freq_mhz( const double &freq_mhz ) 
    { _collection_freq_mhz = freq_mhz; }

    virtual void slave_collection_freq_mhz( const double &freq_mhz ) 
    { master_collection_freq_mhz(freq_mhz); }
 
    virtual void collection_bw_khz(const double & bw_khz) 
    { _collection_bw_khz = bw_khz; }
    
    //    virtual void modulation (const ProcessingEnums::Modulation &mod) 
    //    { _modulation = mod; }
    
    const std::string &radio_type() const { return _radio_type; }
    
    void initialize();
    
    static std::string snl_wrapper() { return _snl_wrapper; }
    
    friend std::ostream& ::operator << ( std::ostream& os, const Signal& p );
    
    
  private:
  
    double _collection_freq_mhz;
    double _collection_bw_khz;
    double _signal_bw_khz;
    std::string _radio_type;
    //    ProcessingEnums::Modulation _modulation;
    static std::string _snl_wrapper;
};

#endif
