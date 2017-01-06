#ifndef USERALREADYEXISTSEXCEPTION_H
#define USERALREADYEXISTSEXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class UserAlreadyExistsException : public exception
{
  public:
    UserAlreadyExistsException(string userName)
    {
        this->userName = userName;
    }

    virtual const char *what() const throw()
    {
        string errorMessage = "The user with name: '";
        errorMessage += userName;
        errorMessage += "' already exists";

        return errorMessage.c_str();
    }

    ~UserAlreadyExistsException() throw() { }

  private:
    string userName;
};

#endif