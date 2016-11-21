#ifndef GETCONTACTSREQUEST_H
#define GETCONTACTSREQUEST_H

#include "RequestType.h"
#include "RequestBase.h"
#include <string>
using namespace std;

class GetContactsRequest : public RequestBase
{
  public:
    GetContactsRequest(string authToken);

    string GetAuthToken() const;

    virtual RequestType GetRequestType();
    virtual string ToString();

#ifdef SERVER
    virtual ResponseBase *Execute();
#endif

    static GetContactsRequest *Parse(string str);

  private:
    string authToken;
};

#endif