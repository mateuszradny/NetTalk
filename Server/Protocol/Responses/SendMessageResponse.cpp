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

    int responseType = (int)GetResponseType();
    stream.write((char *)&responseType, sizeof(responseType));
    stream.write((char *)&result, sizeof(result));

    return stream.str();
}