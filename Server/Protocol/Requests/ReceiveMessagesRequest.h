#ifndef RECEIVEMESSAGESREQUEST_H
#define RECEIVEMESSAGESREQUEST_H

#include "RequestType.h"
#include "RequestBase.h"
#include <string>
using namespace std;

class ReceiveMessagesRequest : public RequestBase
{
  public:
    ReceiveMessagesRequest(string authToken);

    string GetAuthToken() const;

    virtual RequestType GetRequestType();

#ifdef SERVER

    virtual ResponseBase *Execute();
    virtual void PostExecuteEvent();

#endif

    static ReceiveMessagesRequest *Parse(string str);

  private:
    string authToken;
    vector<MessageViewModel> messages;
};

#endif