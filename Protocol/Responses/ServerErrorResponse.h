#ifndef SERVERERRORRESPONSE_H
#define SERVERERRORRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include <string>
using namespace std;

class ServerErrorResponse : public ResponseBase
{
  public:
    ServerErrorResponse(string errorMessage);

    string GetErrorMessage() const;

    virtual ResponseType GetResponseType() const;
    virtual string ToString() const;

  private:
    string errorMessage;
};

#endif