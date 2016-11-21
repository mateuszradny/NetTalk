#ifndef RESPONSETYPE_H
#define RESPONSETYPE_H

enum class ResponseType
{
    InvalidAuthToken = -2,
    ServerError = -1,
    Ok = 0,
    RegistrationResult = 1,
    LoginResult = 2,
    AddContact = 3,
    GetContacts = 4,
    SendMessage = 5,
    ReceiveMessages = 6,
};

#endif