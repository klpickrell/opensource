#ifndef __SOI_FACTORY_H__
#define __SOI_FACTORY_H__
#include <map>
#include <string>
#include "SOI.h"


class SOIFactory
{
public:
    static SOIFactory *instance();

    typedef boost::shared_ptr<SOI> (*new_soi_func)(const std::string &headerString);
    void identifier_to_soi(const std::string &id, new_soi_func );

    boost::shared_ptr<SOI> construct_SOI(const std::string &headerString);

private:

    SOIFactory(); //singleton

    std::map<std::string, new_soi_func> _identifier_to_soi;

    template<typename T>
    boost::shared_ptr<SOI> get_SOI_ptr(const std::string &headerString)
    {
        return boost::shared_ptr<SOI> ( new T( headerString) );
    }
    
    template<typename T>
    void register_soi()
    {
        identifier_to_soi(T::snl_wrapper(), get_SOI_ptr<T>);
    }
};

#endif
