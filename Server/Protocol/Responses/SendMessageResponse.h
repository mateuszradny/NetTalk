#ifndef SENDMESSAGERESPONSE_H
#define SENDMESSAGERESPONSE_H

enum class SendMessageResult
{
    Ok,
    UserNotFound,
};

class SendMessageResponse : public ResponseBase
{
  public:
    SendMessageResponse(SendMessageResult result);

    SendMessageResult GetResult() const;

    virtual ResponseType GetResponseType() const;
    virtual string ToString() const;

  private:
    SendMessageResult result;
};

#endif