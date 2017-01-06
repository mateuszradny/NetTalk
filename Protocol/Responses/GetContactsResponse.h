#ifndef GETCONTACTSRESPONSE_H
#define GETCONTACTSRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include "../../ViewModel/ContactViewModel.h"
#include <string>
using namespace std;

class GetContactsResponse : public ResponseBase
{
  public:
    GetContactsResponse(vector<ContactViewModel> contacts);

    vector<ContactViewModel> GetContacts() const;

    virtual ResponseType GetResponseType() const;
    virtual string ToString() const;

  private:
    vector<ContactViewModel> contacts;
};

#endif