#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H

enum class RequestType
{
    Registration,
    Login,
    AddContact,
    GetContacts,
    RemoveContact,
    SendMessage,
    ReceiveMessages,
    Logout
};

#endif