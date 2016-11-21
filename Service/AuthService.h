#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

class AuthService
{
public:
  static const int MAX_INACTIVITY_IN_SECONDS = 15;

  AuthService(UserRepository *userRepository);

  User Auth(string token);
  bool IsOnline(string userName);
  string LogIn(string userName, string password);
  void Register(string userName, string password);

private:
  UserRepository *userRepository;

  string GetHash(string text);
  bool IsValidToken(string token, User user);
  void ThrowIfInvalidUserName(string userName);
  void ThrowIfInvalidPassword(string password);
  void UpdateLastActivity(User user);
};

#endif