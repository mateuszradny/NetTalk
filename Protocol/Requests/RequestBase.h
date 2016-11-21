#ifndef REQUESTBASE_H
#define REQUESTBASE_H

#include "RequestType.h"
#include "../Responses/ResponseBase.h"
#include <string>
#include <sstream>
using namespace std;

class RequestBase
{
public:
  virtual RequestType GetRequestType() = 0;

#ifdef SERVER

  virtual void PreExecuteEvent() { }

  virtual ResponseBase *Execute() = 0;

  virtual void PostExecuteEvent() { }
  
#endif

  virtual string ToString() = 0;
};

#endif