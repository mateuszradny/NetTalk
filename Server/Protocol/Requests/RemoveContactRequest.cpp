#include "RemoveContactRequest.h"
#include "../Responses/OkResponse.cpp"

RemoveContactRequest::RemoveContactRequest(string authToken, string contactName)
{
    this->authToken = authToken;
    this->contactName = contactName;
}

string RemoveContactRequest::GetAuthToken() const
{
    return this->authToken;
}

string RemoveContactRequest::GetContactName() const
{
    return this->contactName;
}

RequestType RemoveContactRequest::GetRequestType()
{
    return RequestType::RemoveContact;
}

#ifdef SERVER
ResponseBase *RemoveContactRequest::Execute()
{
    string databaseFilePath = "NetTalk.db.sqlite";
    UserRepository userRepository(databaseFilePath);
    ContactRepository contactRepository(databaseFilePath);
    AuthService authService(&userRepository);
    ContactService contactService(&userRepository, &contactRepository, &authService);

    User user = authService.Auth(GetAuthToken());

    contactService.RemoveContact(user.UserName, GetContactName());
    return new OkResponse();
}
#endif

RemoveContactRequest *RemoveContactRequest::Parse(string str)
{
    istringstream stream(str);

    int requestType;
    string authToken, contactName;

    stream >> requestType >> authToken >> contactName;
    if ((RequestType)requestType != RequestType::RemoveContact)
        throw "Invalid type of request";

    return new RemoveContactRequest(authToken, contactName);
}