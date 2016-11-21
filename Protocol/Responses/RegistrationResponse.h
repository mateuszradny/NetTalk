#ifndef REGISTRATIONRESPONSE_H
#define REGISTRATIONRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include <string>
using namespace std;

enum class RegistrationResult
{
  Ok,
  InvalidPassword,
  InvalidUserName,
  UserAlreadyExists,
};

class RegistrationResponse : public ResponseBase
{
public:
  RegistrationResponse(RegistrationResult result);

  RegistrationResult GetResult() const;

  virtual ResponseType GetResponseType() const;
  virtual string ToString() const;

  static RegistrationResponse *Parse(string str);

private:
  RegistrationResult result;
};

#endif