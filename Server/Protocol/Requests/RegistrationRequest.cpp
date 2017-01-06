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

    int requestType, length;
    stream.read((char *)&requestType, sizeof(requestType));

    if ((RequestType)requestType != RequestType::Registration)
        throw "Invalid type of request";

    stream.read((char *)&length, sizeof(length));
    string userName(length, ' ');
    stream.read(&userName[0], length);

    stream.read((char *)&length, sizeof(length));
    string password(length, ' ');
    stream.read(&password[0], length);

    return new RegistrationRequest(userName, password);
}