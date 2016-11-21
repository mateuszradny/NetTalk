#ifndef RESPONSEBASE_H
#define RESPONSEBASE_H

#include "ResponseType.h"
#include <string>
using namespace std;

class ResponseBase
{
public:
  virtual ResponseType GetResponseType() const = 0;
  virtual string ToString() const = 0;
};

#endif