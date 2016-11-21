#include "InvalidAuthTokenResponse.h"

ResponseType InvalidAuthTokenResponse::GetResponseType() const
{
    return ResponseType::InvalidAuthToken;
}

string InvalidAuthTokenResponse::ToString() const
{
    ostringstream stream;
    stream << (int)GetResponseType();
    return stream.str();
}

InvalidAuthTokenResponse *InvalidAuthTokenResponse::Parse(string str)
{
    istringstream stream(str);
    int responseType, result;
    stream >> responseType;

    if ((ResponseType)responseType != ResponseType::InvalidAuthToken)
        throw "Invalid type of request";

    return new InvalidAuthTokenResponse();
}