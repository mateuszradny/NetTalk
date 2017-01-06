#ifndef INVALIDUSERNAMEEXCEPTION_H
#define INVALIDUSERNAMEEXCEPTION_H

#include <exception>
using namespace std;

class InvalidUserNameException : public exception
{
  public:
    virtual const char *what() const throw()
    {
        return "Invalid user name";
    }

    ~InvalidUserNameException() throw() {}
};

#endif