#ifndef INVALIDPASSWORDEXCEPTION_H
#define INVALIDPASSWORDEXCEPTION_H

#include <exception>
using namespace std;

class InvalidPasswordException : public exception
{
    virtual const char *what() const throw()
    {
        return "Invalid password";
    }
};

#endif