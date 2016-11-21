#include "AuthService.h"
#include "CryptoService.cpp"
#include "../Exception/InvalidAuthTokenException.h"
#include "../Exception/InvalidCredentialsException.h"
#include "../Exception/InvalidUserNameException.h"
#include "../Exception/InvalidPasswordException.h"

AuthService::AuthService(UserRepository *userRepository)
{
    if (userRepository == nullptr)
        throw "User repository is null";

    this->userRepository = userRepository;
}

User AuthService::Auth(string token)
{
    User user = userRepository->GetByToken(token);

    if (!IsValidToken(token, user))
        throw InvalidAuthTokenException();

    UpdateLastActivity(user);
    return user;
}

bool AuthService::IsOnline(string userName)
{
    User user = userRepository->GetByUserName(userName);

    double difference = difftime(time(nullptr), user.LastActivity);
    if (difference > AuthService::MAX_INACTIVITY_IN_SECONDS)
        return false;

    return true;
}

string AuthService::LogIn(string userName, string password)
{
    User user = userRepository->GetByUserName(userName);

    if (user.PasswordHash != GetHash(password))
        throw InvalidCredentialsException();

    UpdateLastActivity(user);
    return user.Token;
}

void AuthService::Register(string userName, string password)
{
    ThrowIfInvalidUserName(userName);
    ThrowIfInvalidPassword(password);

    User user;
    user.UserName = userName;
    user.PasswordHash = GetHash(password);

    userRepository->Add(user);
}

string AuthService::GetHash(string text)
{
    return md5(text);
}

bool AuthService::IsValidToken(string token, User user)
{
    if (token != user.Token)
        return false;

    double difference = difftime(time(nullptr), user.LastActivity);
    if (difference > AuthService::MAX_INACTIVITY_IN_SECONDS)
        return false;

    return true;
}

void AuthService::ThrowIfInvalidUserName(string userName)
{
    if (userName.size() < 5)
        throw InvalidUserNameException();

    for (int i = 0; i < userName.size(); i++)
        if (!isalnum(userName[i]))
            throw InvalidUserNameException();
}

void AuthService::ThrowIfInvalidPassword(string password)
{
    if (password.size() < 5)
        throw InvalidPasswordException();

    string allowedCharacters = ",<.>/?;:'\"[{]}\\|=+-_)(*&^%$#@! ";
    for (int i = 0; i < password.size(); i++)
        if (!isalnum(password[i]) && allowedCharacters.find(password[i]) == string::npos)
            throw InvalidPasswordException();
}

void AuthService::UpdateLastActivity(User user)
{
    user.LastActivity = time(nullptr);
    
    userRepository->UpdateLastActivity(user);
}