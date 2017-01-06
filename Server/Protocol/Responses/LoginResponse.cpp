#include "LoginResponse.h"

LoginResponse::LoginResponse(LoginResult result, string authToken)
{
    this->authToken = authToken;
    this->result = result;
}

string LoginResponse::GetAuthToken() const
{
    return this->authToken;
}

LoginResult LoginResponse::GetResult() const
{
    return this->result;
}

ResponseType LoginResponse::GetResponseType() const
{
    return ResponseType::LoginResult;
}

string LoginResponse::ToString() const
{
    ostringstream stream;

    int responseType = (int)GetResponseType();
    stream.write((char *)&responseType, sizeof(responseType));
    stream.write((char *)&result, sizeof(result));

    int tokenLength = authToken.length();
    stream.write((char *)&tokenLength, sizeof(tokenLength));
    stream.write(&authToken[0], tokenLength);

    return stream.str();
}