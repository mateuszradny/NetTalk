#ifndef REMOVECONTACTRESPONSE_H
#define REMOVECONTACTRESPONSE_H

#include "ResponseBase.h"
#include "ResponseType.h"
#include <string>
using namespace std;

class OkResponse : public ResponseBase
{
public:
  virtual ResponseType GetResponseType() const;
  virtual string ToString() const;
};

#endif