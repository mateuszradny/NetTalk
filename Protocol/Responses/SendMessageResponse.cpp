#include "SendMessageResponse.h"

SendMessageResponse::SendMessageResponse(SendMessageResult result)
{
    this->result = result;
}

SendMessageResult SendMessageResponse::GetResult() const
{
    return this->result;
}

ResponseType SendMessageResponse::GetResponseType() const
{
    return ResponseType::SendMessage;
}

string SendMessageResponse::ToString() const
{
    ostringstream stream;
    stream << (int)GetResponseType() << ' ' << (int)GetResult();
    return stream.str();
}

SendMessageResponse *SendMessageResponse::Parse(string str)
{
    istringstream stream(str);
    int responseType, result;
    stream >> responseType >> result;

    if ((ResponseType)responseType != ResponseType::SendMessage)
        throw "Invalid type of request";

    return new SendMessageResponse((SendMessageResult)result);
}