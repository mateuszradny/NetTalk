#ifndef REMOVECONTACTREQUEST_H
#define REMOVECONTACTREQUEST_H

class RemoveContactRequest : public RequestBase
{
  public:
    RemoveContactRequest(string authToken, string contactName);

    string GetAuthToken() const;
    string GetContactName() const;

    virtual RequestType GetRequestType();
    virtual string ToString();

#ifdef SERVER
    virtual ResponseBase *Execute();
#endif

    static RemoveContactRequest *Parse(string str);

  private:
    string authToken;
    string contactName;
};

#endif