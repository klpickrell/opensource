#include <cstdio>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>

namespace io = boost::iostreams;
using namespace std;

int main()
{
    boost::shared_ptr<FILE> handle( popen("./shell_script.sh", "r"),
                                    pclose );

    if( handle ) {
        io::stream_buffer<io::file_descriptor_source> fpstream(fileno(handle.get()));
        std::istream in(&fpstream);
        istream_iterator<string> begin( in ), end;
        vector<string> lines;
        copy( begin, end, back_inserter( lines ) );
        copy( lines.begin(), lines.end(), ostream_iterator<string>( cout, "\n" ) );
    } else {
        throw std::runtime_error( "unable to access shell_script.sh" );
    }
/*

// A less clever way to do it

    std::string line;
    while (in)
    {
        std::getline (in, line);
        std::cout << line << std::endl;
    }
*/

    return 0;
}
