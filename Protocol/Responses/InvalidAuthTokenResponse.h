#ifndef INVALIDAUTHTOKENRESPONSE_H
#define INVALIDAUTHTOKENRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include <string>
using namespace std;

class InvalidAuthTokenResponse : public ResponseBase
{
public:
  virtual ResponseType GetResponseType() const;
  virtual string ToString() const;

  static InvalidAuthTokenResponse *Parse(string str);
};

#endif