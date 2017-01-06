#include "AddContactRequest.h"
#include "../Responses/AddContactResponse.cpp"
#include "../../Service/ContactService.cpp"

AddContactRequest::AddContactRequest(string authToken, string contactName)
{
    this->authToken = authToken;
    this->contactName = contactName;
}

string AddContactRequest::GetAuthToken() const
{
    return this->authToken;
}

string AddContactRequest::GetContactName() const
{
    return this->contactName;
}

RequestType AddContactRequest::GetRequestType()
{
    return RequestType::AddContact;
}

#ifdef SERVER
ResponseBase *AddContactRequest::Execute()
{
    try
    {
        string databaseFilePath = "NetTalk.db.sqlite";
        UserRepository userRepository(databaseFilePath);
        ContactRepository contactRepository(databaseFilePath);
        AuthService authService(&userRepository);
        ContactService contactService(&userRepository, &contactRepository, &authService);

        User user = authService.Auth(GetAuthToken());
            
        contactService.AddContact(user.UserName, GetContactName());
        return new AddContactResponse(AddContactResult::Ok);
    }
    catch (UserNotFoundException &ex)
    {
        return new AddContactResponse(AddContactResult::UserNotFound);
    }
}
#endif

AddContactRequest *AddContactRequest::Parse(string str)
{
    istringstream stream(str);

    int requestType, length;
    stream.read((char *)&requestType, sizeof(requestType));
    if ((RequestType)requestType != RequestType::AddContact)
        throw "Invalid type of request";

    stream.read((char *)&length, sizeof(length));
    string authToken(length, ' ');
    stream.read(&authToken[0], length);

    stream.read((char *)&length, sizeof(length));
    string contactName(length, ' ');
    stream.read(&contactName[0], length);

    return new AddContactRequest(authToken, contactName);
}