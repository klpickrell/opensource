#ifndef ETHERNET_FRAME__H
#define ETHERNET_FRAME__H

#include <exception>
#include <string>
#include <vector>

// SYNC | Sequence Num | Total Messages | Frame ID | From | To | Data Length | Data
//  4           4               4            4        16    16        4          N
namespace Ethernet 
{
    class FormatError : public std::exception
    {
    public:
        FormatError( const std::string& what ) :
            _what( what ) {}

        ~FormatError() throw() {}

        const char* what() const throw() { return _what.c_str(); }

    private:

        std::string _what;
    };

    struct Header {
        char sync[4];
        unsigned int sequence_num;
        unsigned int total_frames;
        unsigned int frame_id;
        char from[16];
        char to[16];
        unsigned int data_length;
    };

    static const int MAX_IDENTIFIER_LENGTH = 15;
    static const int FRAME_HEADER_LENGTH = sizeof(Header);
    static const int SYNC_SIZE = 4;
    static const char* sync_string = "\xFF\xFE\xFF\xFE";
    static const int BYTE_ORDER_NETWORK = 1;
    static const int BYTE_ORDER_HOST = 2;

    class Frame
    {
    public:

        Frame( const std::vector<char>& frame, int byte_order = BYTE_ORDER_HOST ) throw( FormatError );
        Frame( const char* source, int length, int byte_order = BYTE_ORDER_HOST ) throw( FormatError );

        void setBuffer( const char* source, int length ) throw( FormatError );
        void setBuffer( const std::vector<char>& src ) throw( FormatError ) {
            return setBuffer( &src[0], src.size() );
        }

        int length() const { return _data.size(); }

        unsigned int data_length() const;
        unsigned int sequence_num() const;
        unsigned int total_frames() const;
        unsigned int frame_id() const;

        std::string to() const;
        std::string from() const;
        std::vector<char> data() const;

        const std::vector<char>& buffer() const { return _data; }

        bool network_order() const { return byte_order == BYTE_ORDER_NETWORK; }
        bool host_order() const { return byte_order == BYTE_ORDER_HOST; }

    private:

        int byte_order;
        std::vector<char> _data;
    };
}

std::ostream& operator<<( std::ostream& lhs, const Ethernet::Frame& frame );

#endif
