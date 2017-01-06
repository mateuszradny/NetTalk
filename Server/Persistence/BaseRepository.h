#ifndef BASEREPOSITORY_H
#define BASEREPOSITORY_H

#include <string>
#include "../ExternalLibraries/sqlite3.h"
using namespace std;

class BaseRepository
{
protected:
  BaseRepository(string databaseFilePath);

  void CloseDatabase();
  void ExecuteNonQuery(string command);
  string NewGuid();
  void OpenDatabase();
  sqlite3_stmt *PrepareQuery(string query);

private:
  string databaseFilePath;
  sqlite3 *database;
};

#endif