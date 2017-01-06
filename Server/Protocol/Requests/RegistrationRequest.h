#ifndef REGISTRATIONREQUEST_H
#define REGISTRATIONREQUEST_H

#include "RequestType.h"
#include "RequestBase.h"
#include <string>
using namespace std;

class RegistrationRequest : public RequestBase
{
public:
  RegistrationRequest(string userName, string password);

  string GetUserName() const;
  string GetPassword() const;

  virtual RequestType GetRequestType();

#ifdef SERVER
  virtual ResponseBase *Execute();
#endif

  static RegistrationRequest *Parse(string str);

private:
  string userName;
  string password;
};

#endif