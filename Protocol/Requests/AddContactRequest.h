#ifndef ADDCONTACTREQUEST_H
#define ADDCONTACTREQUEST_H

#include "RequestType.h"
#include "RequestBase.h"
#include <string>
using namespace std;

class AddContactRequest : public RequestBase
{
  public:
    AddContactRequest(string authToken, string contactName);

    string GetAuthToken() const;
    string GetContactName() const;

    virtual RequestType GetRequestType();
    virtual string ToString();

#ifdef SERVER
    virtual ResponseBase *Execute();
#endif

    static AddContactRequest *Parse(string str);

  private:
    string authToken;
    string contactName;
};

#endif