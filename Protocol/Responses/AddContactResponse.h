#ifndef ADDCONTACTRESPONSE_H
#define ADDCONTACTRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include <string>
using namespace std;

enum class AddContactResult
{
  Ok,
  UserNotFound,
};

class AddContactResponse : public ResponseBase
{
public:
  AddContactResponse(AddContactResult result);

  AddContactResult GetResult() const;

  virtual ResponseType GetResponseType() const;
  virtual string ToString() const;

  static AddContactResponse *Parse(string str);

private:
  AddContactResult result;
};

#endif