#ifndef INVALIDCREDENTIALSEXCEPTION_H
#define INVALIDCREDENTIALSEXCEPTION_H

#include <exception>
using namespace std;

class InvalidCredentialsException : public exception
{
  public:
    virtual const char *what() const throw()
    {
        return "Invalid username and/or password";
    }

    ~InvalidCredentialsException() throw() {}
};

#endif