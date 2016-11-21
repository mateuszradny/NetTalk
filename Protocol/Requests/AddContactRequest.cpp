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

string AddContactRequest::ToString()
{
    ostringstream stream;
    stream << (int)GetRequestType() << ' ' << GetAuthToken() << ' ' << GetContactName();

    return stream.str();
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

    int requestType;
    string authToken, contactName;

    stream >> requestType >> authToken >> contactName;
    if ((RequestType)requestType != RequestType::AddContact)
        throw "Invalid type of request";

    return new AddContactRequest(authToken, contactName);
}