#ifndef SENDMESSAGEREQUEST_H
#define SENDMESSAGEREQUEST_H

#include "RequestBase.h"
#include "RequestType.h"
#include <string>
using namespace std;

class SendMessageRequest : public RequestBase
{
public:
  SendMessageRequest(string authToken, string message, string recipientName);

  string GetAuthToken() const;
  string GetMessage() const;
  string GetRecipientName() const;

  virtual RequestType GetRequestType();
  virtual string ToString();

#ifdef SERVER
  ResponseBase *Execute();
#endif

  static SendMessageRequest *Parse(string str);

private:
  string authToken;
  string message;
  string recipientName;
};

#endif