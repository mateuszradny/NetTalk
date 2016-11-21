#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "RequestType.h"
#include "RequestBase.h"
#include <string>
using namespace std;

class LoginRequest : public RequestBase
{
public:
  LoginRequest(string userName, string password);

  string GetUserName() const;
  string GetPassword() const;

  virtual RequestType GetRequestType();
  virtual string ToString();

#ifdef SERVER
  virtual ResponseBase *Execute();
#endif

  static LoginRequest *Parse(string str);

private:
  string userName;
  string password;
};

#endif