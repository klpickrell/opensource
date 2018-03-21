#ifndef COMBINE_REQUEST__H
#define COMBINE_REQUEST__H

#include <vector>
#include <stdexcept>
#include <boost/tuple/tuple.hpp>

class GeoID
{
    typedef boost::tuple<std::string,
                         std::string,
                         std::string,
                         int> geo_id_tuple;

public:
    GeoID( const std::string& productID,
           const std::string& activityID,
           const std::string& actionID,
           int index ) :
        m_id( boost::make_tuple( productID, activityID, actionID, index ) )
    {}

    std::string productID() const { return m_id.get<0>(); }
    std::string activityID() const { return m_id.get<1>(); }
    std::string actionID() const { return m_id.get<2>(); }
    int index() const { return m_id.get<3>(); }
    
private:

    geo_id_tuple m_id;
};

class combine_parse_error : public std::runtime_error
{
public:
    combine_parse_error( const std::string& what ) :
        std::runtime_error( what )
    {}
};

class CombineRequest
{
public:
    CombineRequest( const std::string& text,
                    const std::string& geos ) throw( combine_parse_error );

    std::vector<GeoID> getGeos() const { return m_geos; }

private:

    void addCombine( const boost::tuple<std::string,std::string,std::string,int>& t )
    { m_geos.push_back( GeoID( t.get<0>(), t.get<1>(), t.get<2>(), t.get<3>() ) ); }
    
    std::string m_text;
    std::vector<GeoID> m_geos;
};

#endif
