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

    int responseType = (int)GetResponseType();
    stream.write((char *)&responseType, sizeof(responseType));

    int messageCount = messages.size();
    stream.write((char *)&messageCount, sizeof(messageCount));

    for (int i = 0; i < messageCount; i++)
    {
        int length = messages[i].SenderName.size();
        stream.write((char *)&length, sizeof(length));
        stream.write(&(messages[i].SenderName[0]), length);

        stream.write((char *)&(messages[i].PostDate), sizeof(messages[i].PostDate));

        length = messages[i].Body.size();
        stream.write((char *)&length, sizeof(length));
        stream.write(&(messages[i].Body[0]), length);
    }

    return stream.str();
}