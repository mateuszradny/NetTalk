#ifndef SERVERSERVICE_H
#define SERVERSERVICE_H

#include "../Protocol/Requests/RequestBase.h"
#include <string>
using namespace std;

class ServerService
{
public:
  void ExecuteRequest(int fd);
  RequestBase *ReadRequest(int fd);
  void WriteResponse(int fd, ResponseBase *response);

private:
  ResponseBase *ExecuteRequestAndGetResponse(RequestBase *request);
  int ReadRequestSize(int fd);
  string ReadRequestBody(int fd, int requestSize);
  RequestType GetRequestType(string requestBody);
  RequestBase *GetRequest(RequestType requestType, string requestBody);
};

#endif