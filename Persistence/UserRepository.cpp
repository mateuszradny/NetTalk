#include <string>
#include "UserRepository.h"
#include "../Exception/InvalidAuthTokenException.h"
#include "../Exception/UserAlreadyExistsException.h"
#include "../Exception/UserNotFoundException.h"
#include "../ExternalLibraries/sqlite3.h"
using namespace std;

UserRepository::UserRepository(string databaseFilePath) : BaseRepository(databaseFilePath)
{
}

void UserRepository::Add(User user)
{
    if (Exists(user.UserName))
        throw UserAlreadyExistsException(user.UserName);

    user.LastActivity = 0;

    OpenDatabase();
    string command = GetInsertCommand(user);
    ExecuteNonQuery(command);
    CloseDatabase();
}

bool UserRepository::Exists(string userName)
{
    try
    {
        GetByUserName(userName);
        return true;
    }
    catch (UserNotFoundException)
    {
        return false;
    }
}

User UserRepository::GetByToken(string token)
{
    OpenDatabase();
    string query = GetSelectByTokenQuery(token);
    vector<User> users = ExecuteSelectQuery(query);
    CloseDatabase();

    if (users.size() == 0)
        throw InvalidAuthTokenException();

    return users[0];
}

User UserRepository::GetByUserName(string userName)
{
    OpenDatabase();
    string query = GetSelectByUserNameQuery(userName);
    vector<User> users = ExecuteSelectQuery(query);
    CloseDatabase();

    if (users.size() == 0)
        throw UserNotFoundException(userName);

    return users[0];
}

void UserRepository::UpdateLastActivityAndToken(User user)
{
    OpenDatabase();
    string command = GetUpdateLastActivityAndTokenCommand(user);
    ExecuteNonQuery(command);
    CloseDatabase();
}

vector<User> UserRepository::ExecuteSelectQuery(string query)
{
    vector<User> users;

    sqlite3_stmt *statement = PrepareQuery(query);
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        User user;
        user.UserName = (char *)sqlite3_column_text(statement, 0);
        user.PasswordHash = (char *)sqlite3_column_text(statement, 1);
        user.LastActivity = (long int)sqlite3_column_int(statement, 2);
        user.Token = (char *)sqlite3_column_text(statement, 3);

        users.push_back(user);
    }

    return users;
}

string UserRepository::GetInsertCommand(User user)
{
    string command;

    command.append("INSERT INTO Users (UserName, PasswordHash, LastActivity, Token) VALUES('");
    command.append(user.UserName);
    command.append("', '");
    command.append(user.PasswordHash);
    command.append("', '");
    command.append(to_string((long int)user.LastActivity));
    command.append("', '");
    command.append(user.Token);
    command.append("');");

    return command;
}

string UserRepository::GetSelectByTokenQuery(string token)
{
    string query;

    query.append("SELECT UserName, PasswordHash, LastActivity, Token FROM Users WHERE Token='");
    query.append(token);
    query.append("';");

    return query;
}

string UserRepository::GetSelectByUserNameQuery(string userName)
{
    string query;

    query.append("SELECT UserName, PasswordHash, LastActivity, Token FROM Users WHERE UserName='");
    query.append(userName);
    query.append("';");

    return query;
}

string UserRepository::GetUpdateLastActivityAndTokenCommand(User user)
{
    string command;

    command.append("UPDATE Users SET LastActivity='");
    command.append(to_string((long int)user.LastActivity));
    command.append("', Token='");
    command.append(user.Token);
    command.append("' WHERE UserName='");
    command.append(user.UserName);
    command.append("';");

    return command;
}