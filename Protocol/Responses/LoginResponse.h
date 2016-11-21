#ifndef LOGINRESPONSE_H
#define LOGINRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include <string>
using namespace std;

enum class LoginResult
{
    Ok,
    InvalidCredentials,
};

class LoginResponse : public ResponseBase
{
  public:
    LoginResponse(LoginResult result, string authToken = "");

    string GetAuthToken() const;
    LoginResult GetResult() const;

    virtual ResponseType GetResponseType() const;
    virtual string ToString() const;

    static LoginResponse *Parse(string str);

  private:
    string authToken;
    LoginResult result;
};

#endif