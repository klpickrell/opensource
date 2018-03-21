#include <iostream>
#include <string>

using namespace std;


class myclass
{
public:
    myclass( const std::string& name,
             const std::string& value = (std::string( "Enter value for " ) + std::string( name ) + ":" ) ) :
        _name( name ),
        _value( value )
    {
    }

private:
    
    std::string _name;
    std::string _value;
};

int main( int argc, char** argv )
{
  return 0;
}


