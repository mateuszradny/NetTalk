#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class SqlException : public exception
{
  public:
    SqlException(string errorMessage)
    {
        this->errorMessage = errorMessage;
    }

    virtual const char *what() const throw()
    {
        return this->errorMessage.c_str();
    }

    ~SqlException() throw() { }

  private:
    string errorMessage;
};

#endif