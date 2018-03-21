#include <cstring>
#include <boost/lexical_cast.hpp>
#include "ErrnoException.h"

ErrnoException::ErrnoException(int error, const std::string& syscall) :
    std::runtime_error("Errno [" + boost::lexical_cast<std::string>(error) +
                       "] " + "during " + syscall + ": " + strerror(error)),
    error(error),
    syscall(syscall)
{
}
