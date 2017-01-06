#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>
using namespace std;

class User
{
public:
  string UserName;
  string PasswordHash;
  
  time_t LastActivity;
  string Token;
};

#endif