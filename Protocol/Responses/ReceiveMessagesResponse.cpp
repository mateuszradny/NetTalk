#include "ReceiveMessagesResponse.h"

ReceiveMessagesResponse::ReceiveMessagesResponse(vector<MessageViewModel> messages)
{
    this->messages = messages;
}

vector<MessageViewModel> ReceiveMessagesResponse::GetMessages() const
{
    return this->messages;
}

ResponseType ReceiveMessagesResponse::GetResponseType() const
{
    return ResponseType::ReceiveMessages;
}

string ReceiveMessagesResponse::ToString() const
{
    ostringstream stream;
    stream << (int)GetResponseType() << ' ' << messages.size();
    for (int i = 0; i < messages.size(); i++)
    {
        stream << ' ' << messages[i].Id
               << ' ' << messages[i].SenderName
               << ' ' << messages[i].PostDate
               << ' ' << messages[i].Body
               << endl;
    }
    return stream.str();
}

ReceiveMessagesResponse *ReceiveMessagesResponse::Parse(string str)
{
    istringstream stream(str);
    int responseType, messageCount;
    stream >> responseType >> messageCount;

    if ((ResponseType)responseType != ResponseType::ReceiveMessages)
        throw "Invalid type of request";

    vector<MessageViewModel> messages;
    for (int i = 0; i < messageCount; i++)
    {
        MessageViewModel message;
        stream >> message.Id >> message.SenderName >> message.PostDate;
        getline(stream, message.Body);

        messages.push_back(message);
    }

    return new ReceiveMessagesResponse(messages);
}