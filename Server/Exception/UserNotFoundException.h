#ifndef USERNOTFOUNDEXCEPTION_H
#define USERNOTFOUNDEXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class UserNotFoundException : public exception
{
  public:
    UserNotFoundException(string userName)
    {
        this->userName = userName;
    }

    virtual const char *what() const throw()
    {
        string errorMessage = "Not found user with name: ";
        errorMessage += userName;

        return errorMessage.c_str();
    }

    ~UserNotFoundException() throw() { }

  private:
    string userName;
};

#endif