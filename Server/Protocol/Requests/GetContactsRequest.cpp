#include "GetContactsRequest.h"
#include "../Responses/GetContactsResponse.cpp"

GetContactsRequest::GetContactsRequest(string authToken)
{
    this->authToken = authToken;
}

string GetContactsRequest::GetAuthToken() const
{
    return this->authToken;
}

RequestType GetContactsRequest::GetRequestType()
{
    return RequestType::GetContacts;
}

#ifdef SERVER
ResponseBase *GetContactsRequest::Execute()
{
    string databaseFilePath = "NetTalk.db.sqlite";
    UserRepository userRepository(databaseFilePath);
    ContactRepository contactRepository(databaseFilePath);
    AuthService authService(&userRepository);
    ContactService contactService(&userRepository, &contactRepository, &authService);

    User user = authService.Auth(GetAuthToken());
    vector<ContactViewModel> contacts = contactService.GetContactsByUserName(user.UserName);

    return new GetContactsResponse(contacts);
}
#endif

GetContactsRequest *GetContactsRequest::Parse(string str)
{
    istringstream stream(str);

    int requestType, length;
    stream.read((char *)&requestType, sizeof(requestType));
    if ((RequestType)requestType != RequestType::GetContacts)
        throw "Invalid type of request";

    stream.read((char *)&length, sizeof(length));
    string authToken(length, ' ');
    stream.read(&authToken[0], length);
    return new GetContactsRequest(authToken);
}