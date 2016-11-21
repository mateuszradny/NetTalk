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
    stream << (int)GetResponseType() << ' ' << (int)GetResult() << ' ' << GetAuthToken();
    return stream.str();
}

LoginResponse *LoginResponse::Parse(string str)
{
    istringstream stream(str);
    int responseType, result;
    string authToken;
    stream >> responseType >> result >> authToken;

    if ((ResponseType)responseType != ResponseType::LoginResult)
        throw "Invalid type of request";

    return new LoginResponse((LoginResult)result, authToken);
}