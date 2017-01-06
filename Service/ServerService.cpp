#include "ServerService.h"
#include "../Protocol/Requests/AddContactRequest.cpp"
#include "../Protocol/Requests/GetContactsRequest.cpp"
#include "../Protocol/Requests/RemoveContactRequest.cpp"
#include "../Protocol/Requests/LoginRequest.cpp"
#include "../Protocol/Requests/RegistrationRequest.cpp"
#include "../Protocol/Requests/SendMessageRequest.cpp"
#include "../Protocol/Requests/ReceiveMessagesRequest.cpp"
#include "../Protocol/Responses/InvalidAuthTokenResponse.cpp"
#include "../Protocol/Responses/RegistrationResponse.cpp"
#include "../Protocol/Responses/ServerErrorResponse.cpp"
#include <sstream>
using namespace std;

RequestBase *ServerService::ReadRequest(int fd)
{
    int requestSize = ReadRequestSize(fd);
    string requestBody = ReadRequestBody(fd, requestSize);
    RequestType requestType = GetRequestType(requestBody);

    return GetRequest(requestType, requestBody);
}

int ServerService::ReadRequestSize(int fd)
{
    int size;
    read(fd, &size, sizeof(size));
    return size;
}

string ServerService::ReadRequestBody(int fd, int requestSize)
{
    char bytes[requestSize];
    read(fd, bytes, sizeof(bytes));

    string body;
    body.resize(sizeof(bytes));
    memcpy(&body[0], bytes, sizeof(bytes));

    return body;
}

RequestType ServerService::GetRequestType(string requestBody)
{
    int requestType;
    
    istringstream stream(requestBody);
    stream.read((char*)&requestType, sizeof(requestType));

    return (RequestType)requestType;
}

RequestBase *ServerService::GetRequest(RequestType requestType, string requestBody)
{
    switch (requestType)
    {
    case RequestType::Registration:
        return RegistrationRequest::Parse(requestBody);
    case RequestType::Login:
        return LoginRequest::Parse(requestBody);
    case RequestType::AddContact:
        return AddContactRequest::Parse(requestBody);
    case RequestType::GetContacts:
        return GetContactsRequest::Parse(requestBody);
    case RequestType::RemoveContact:
        return RemoveContactRequest::Parse(requestBody);
    case RequestType::SendMessage:
        return SendMessageRequest::Parse(requestBody);
    case RequestType::ReceiveMessages:
        return ReceiveMessagesRequest::Parse(requestBody);
    default:
        return nullptr;
    }
}

void ServerService::WriteResponse(int fd, ResponseBase *response)
{
    string responseBody = response->ToString();
    int responseSize = responseBody.size();
    write(fd, &responseSize, sizeof(responseSize));
    write(fd, &responseBody[0], responseSize);
}

void ServerService::ExecuteRequest(int fd)
{
    RequestBase *request = ReadRequest(fd);
    ResponseBase *response = ExecuteRequestAndGetResponse(request);
    WriteResponse(fd, response);

    delete request;
    delete response;
}

ResponseBase *ServerService::ExecuteRequestAndGetResponse(RequestBase *request)
{
    try
    {
        request->PreExecuteEvent();
        ResponseBase *response = request->Execute();
        request->PostExecuteEvent();

        return response;
    }
    catch (InvalidAuthTokenException &ex)
    {
        return new InvalidAuthTokenResponse();
    }
    catch (const exception &ex)
    {
        return new ServerErrorResponse(ex.what());
    }
    catch (const string &ex)
    {
        return new ServerErrorResponse(ex);
    }
    catch (...)
    {
        return new ServerErrorResponse("Unknown Error");
    }
}