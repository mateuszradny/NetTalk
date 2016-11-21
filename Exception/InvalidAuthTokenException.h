#ifndef INVALIDAUTHTOKENEXCEPTION_H
#define INVALIDAUTHTOKENEXCEPTION_H

#include <exception>
using namespace std;

class InvalidAuthTokenException : public exception
{
    virtual const char *what() const throw()
    {
        return "Invalid auth token";
    }
};

#endif