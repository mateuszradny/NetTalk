#include "ServerErrorResponse.h"

ServerErrorResponse::ServerErrorResponse(string errorMessage)
{
    this->errorMessage = errorMessage;
}

string ServerErrorResponse::GetErrorMessage() const
{
    return this->errorMessage;
}

ResponseType ServerErrorResponse::GetResponseType() const
{
    return ResponseType::ServerError;
}

string ServerErrorResponse::ToString() const
{
    ostringstream stream;

    int responseType = (int)GetResponseType();
    stream.write((char *)&responseType, sizeof(responseType));

    int length = errorMessage.size();
    stream.write((char *)&length, sizeof(length));
    stream.write(&errorMessage[0], length);

    return stream.str();
}