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