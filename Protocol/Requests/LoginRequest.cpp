#include "LoginRequest.h"
#include "../Responses/LoginResponse.h"
#include "../../Exception/InvalidUserNameException.h"
#include "../../Exception/InvalidPasswordException.h"
#include <sstream>
using namespace std;

LoginRequest::LoginRequest(string userName, string password)
{
    this->userName = userName;
    this->password = password;
}

string LoginRequest::GetUserName() const
{
    return userName;
}

string LoginRequest::GetPassword() const
{
    return password;
}

RequestType LoginRequest::GetRequestType()
{
    return RequestType::Login;
}

string LoginRequest::ToString()
{
    ostringstream stream;
    stream << (int)GetRequestType() << ' ' << GetUserName() << ' ' << GetPassword();

    return stream.str();
}

#ifdef SERVER
ResponseBase *LoginRequest::Execute()
{
    try
    {
        UserRepository userRepository("NetTalk.db.sqlite");
        AuthService authService(&userRepository);

        string authToken = authService.LogIn(GetUserName(), GetPassword());
        return new LoginResponse(LoginResult::Ok, authToken);
    }
    catch (InvalidCredentialsException &ex)
    {
        return new LoginResponse(LoginResult::InvalidCredentials);
    }
    catch (UserNotFoundException &ex)
    {
        return new LoginResponse(LoginResult::InvalidCredentials);
    }
}
#endif

LoginRequest *LoginRequest::Parse(string str)
{
    istringstream stream(str);

    int requestType;
    string userName, password;

    stream >> requestType >> userName >> password;
    if ((RequestType)requestType != RequestType::Login)
        throw "Invalid type of request";

    return new LoginRequest(userName, password);
}