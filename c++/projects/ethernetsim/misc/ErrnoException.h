#ifndef ErrnoException_h
#define ErrnoException_h

#include <stdexcept>
#include <string>

class ErrnoException : public std::runtime_error
{
public:
   ErrnoException(int error, const std::string& syscall);
   virtual ~ErrnoException() throw () { }

   int error;
   std::string syscall;
};

#endif  // !ErrnoException_h
