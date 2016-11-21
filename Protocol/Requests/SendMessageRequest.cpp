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

string SendMessageRequest::ToString()
{
    ostringstream stream;
    stream << (int)GetRequestType() << ' ' << GetAuthToken() << ' ' << GetRecipientName() << ' ' << GetMessage();

    return stream.str();
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

    int requestType;
    string authToken, message, recipientName;

    stream >> requestType >> authToken >> recipientName;
    if ((RequestType)requestType != RequestType::SendMessage)
        throw "Invalid type of request";

    getline(stream, message);
    return new SendMessageRequest(authToken, message, recipientName);
}