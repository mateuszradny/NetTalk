#include "RegistrationRequest.h"
#include "../Responses/RegistrationResponse.h"
#include "../../Exception/InvalidUserNameException.h"
#include "../../Exception/InvalidPasswordException.h"
#include <sstream>
using namespace std;

RegistrationRequest::RegistrationRequest(string userName, string password)
{
    this->userName = userName;
    this->password = password;
}

string RegistrationRequest::GetUserName() const
{
    return userName;
}

string RegistrationRequest::GetPassword() const
{
    return password;
}

RequestType RegistrationRequest::GetRequestType()
{
    return RequestType::Registration;
}

string RegistrationRequest::ToString()
{
    ostringstream stream;
    stream << (int)GetRequestType() << ' ' << GetUserName() << ' ' << GetPassword();

    return stream.str();
}

#ifdef SERVER
ResponseBase *RegistrationRequest::Execute()
{
    try
    {
        UserRepository userRepository("NetTalk.db.sqlite");
        AuthService authService(&userRepository);

        authService.Register(GetUserName(), GetPassword());
        return new RegistrationResponse(RegistrationResult::Ok);
    }
    catch (InvalidPasswordException &ex)
    {
        return new RegistrationResponse(RegistrationResult::InvalidPassword);
    }
    catch (InvalidUserNameException &ex)
    {
        return new RegistrationResponse(RegistrationResult::InvalidUserName);
    }
    catch (UserAlreadyExistsException &ex)
    {
        return new RegistrationResponse(RegistrationResult::UserAlreadyExists);
    }
}
#endif

RegistrationRequest *RegistrationRequest::Parse(string str)
{
    istringstream stream(str);

    int requestType;
    string userName, password;

    stream >> requestType >> userName >> password;
    if ((RequestType)requestType != RequestType::Registration)
        throw "Invalid type of request";

    return new RegistrationRequest(userName, password);
}