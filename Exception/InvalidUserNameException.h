#ifndef INVALIDUSERNAMEEXCEPTION_H
#define INVALIDUSERNAMEEXCEPTION_H

#include <exception>
using namespace std;

class InvalidUserNameException : public exception
{
    virtual const char *what() const throw()
    {
        return "Invalid user name";
    }
};

#endif