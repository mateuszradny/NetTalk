#include "ReceiveMessagesRequest.h"
#include "../Responses/ReceiveMessagesResponse.cpp"

ReceiveMessagesRequest::ReceiveMessagesRequest(string authToken)
{
    this->authToken = authToken;
}

string ReceiveMessagesRequest::GetAuthToken() const
{
    return this->authToken;
}

RequestType ReceiveMessagesRequest::GetRequestType()
{
    return RequestType::ReceiveMessages;
}

#ifdef SERVER

ResponseBase *ReceiveMessagesRequest::Execute()
{
    string databaseFilePath = "NetTalk.db.sqlite";
    UserRepository userRepository(databaseFilePath);
    MessageRepository messageRepository(databaseFilePath);
    AuthService authService(&userRepository);
    MessageService messageService(&messageRepository, &userRepository);

    User user = authService.Auth(GetAuthToken());

    messages = messageService.GetUnreadMessages(user.UserName);
    return new ReceiveMessagesResponse(messages);
}

void ReceiveMessagesRequest::PostExecuteEvent()
{
    string databaseFilePath = "NetTalk.db.sqlite";
    UserRepository userRepository(databaseFilePath);
    MessageRepository messageRepository(databaseFilePath);
    MessageService messageService(&messageRepository, &userRepository);

    for (int i = 0; i < messages.size(); i++)
    {
        messageService.SetAsRead(messages[i].Id);
    }
}

#endif

ReceiveMessagesRequest *ReceiveMessagesRequest::Parse(string str)
{
    istringstream stream(str);

    int requestType, length;
    stream.read((char *)&requestType, sizeof(requestType));

    if ((RequestType)requestType != RequestType::ReceiveMessages)
        throw "Invalid type of request";

    stream.read((char *)&length, sizeof(length));
    string authToken(length, ' ');
    stream.read(&authToken[0], length);

    return new ReceiveMessagesRequest(authToken);
}