#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <string>
#include <vector>
#include "../Model/User.h"
#include "BaseRepository.h"
using namespace std;

class UserRepository : public BaseRepository
{
public:
  UserRepository(string databaseFilePath);

  void Add(User user);
  bool Exists(string userName);
  User GetByToken(string token);
  User GetByUserName(string userName);
  void UpdateLastActivity(User user);

private:
  vector<User> ExecuteSelectQuery(string query);
  string GetInsertCommand(User user);
  string GetSelectByTokenQuery(string token);
  string GetSelectByUserNameQuery(string userName);
  string GetUpdateLastActivityCommand(User user);
};

#endif