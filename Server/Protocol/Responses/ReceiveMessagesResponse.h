#ifndef RECEIVEMESSAGESRESPONSE_H
#define RECEIVEMESSAGESRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include <string>
using namespace std;

class ReceiveMessagesResponse : public ResponseBase
{
  public:
    ReceiveMessagesResponse(vector<MessageViewModel> messages);

    vector<MessageViewModel> GetMessages() const;

    virtual ResponseType GetResponseType() const;
    virtual string ToString() const;

  private:
    vector<MessageViewModel> messages;
};

#endif