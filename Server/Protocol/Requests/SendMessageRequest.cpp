#include "SendMessageRequest.h"
#include "../Responses/SendMessageResponse.cpp"
#include "../../Service/MessageService.cpp"

SendMessageRequest::SendMessageRequest(string authToken, string message, string recipientName)
{
    this->authToken = authToken;
    this->message = message;
    this->recipientName = recipientName;
}

string SendMessageRequest::GetAuthToken() const
{
    return this->authToken;
}

string SendMessageRequest::GetMessage() const
{
    return this->message;
}

string SendMessageRequest::GetRecipientName() const
{
    return this->recipientName;
}

RequestType SendMessageRequest::GetRequestType()
{
    return RequestType::SendMessage;
}

#ifdef SERVER
ResponseBase *SendMessageRequest::Execute()
{
    try
    {
        string databaseFilePath = "NetTalk.db.sqlite";
        UserRepository userRepository(databaseFilePath);
        MessageRepository messageRepository(databaseFilePath);
        AuthService authService(&userRepository);
        MessageService messageService(&messageRepository, &userRepository);

        User user = authService.Auth(GetAuthToken());

        messageService.AddMessage(user.UserName, GetRecipientName(), GetMessage());
        return new SendMessageResponse(SendMessageResult::Ok);
    }
    catch (UserNotFoundException &ex)
    {
        return new SendMessageResponse(SendMessageResult::UserNotFound);
    }
}
#endif

SendMessageRequest *SendMessageRequest::Parse(string str)
{
    istringstream stream(str);

    int requestType, length;
    stream.read((char *)&requestType, sizeof(requestType));

    if ((RequestType)requestType != RequestType::SendMessage)
        throw "Invalid type of request";

    stream.read((char *)&length, sizeof(length));
    string authToken(length, ' ');
    stream.read(&authToken[0], length);

    stream.read((char *)&length, sizeof(length));
    string recipientName(length, ' ');
    stream.read(&recipientName[0], length);

    stream.read((char *)&length, sizeof(length));
    string message(length, ' ');
    stream.read(&message[0], length);

    return new SendMessageRequest(authToken, message, recipientName);
}