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
    stream << (int)GetResponseType() << ' ' << GetErrorMessage();
    return stream.str();
}