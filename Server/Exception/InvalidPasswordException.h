#ifndef INVALIDPASSWORDEXCEPTION_H
#define INVALIDPASSWORDEXCEPTION_H

#include <exception>
using namespace std;

class InvalidPasswordException : public exception
{
  public:
    virtual const char *what() const throw()
    {
        return "Invalid password";
    }

    ~InvalidPasswordException() throw() {}
};

#endif