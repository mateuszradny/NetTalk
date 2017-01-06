#include "BaseRepository.h"
#include "../Exception/SqlException.h"

BaseRepository::BaseRepository(string databaseFilePath)
{
    if (databaseFilePath == "")
        throw "Invalid path";

    this->databaseFilePath = databaseFilePath;
}

void BaseRepository::CloseDatabase()
{
    sqlite3_close(database);
}

void BaseRepository::ExecuteNonQuery(string command)
{
    char *errorMessage;
    int resultCode = sqlite3_exec(database, command.c_str(), NULL, 0, &errorMessage);
    if (resultCode != SQLITE_OK)
    {
        SqlException ex(errorMessage);
        sqlite3_free(errorMessage);
        throw ex;
    }
}

string BaseRepository::NewGuid()
{
    char guid[40];
    const char *pattern = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    const char *hex = "0123456789ABCDEF-";
    int length = strlen(pattern);

    for (int t = 0; t < length + 1; t++)
    {
        int r = rand() % 16;
        char c = ' ';

        switch (pattern[t])
        {
        case 'x':
            c = hex[r];
            break;

        case 'y':
            c = hex[r & 0x03 | 0x08];
            break;

        case '-':
            c = '-';
            break;

        case '4':
            c = '4';
            break;
        }

        guid[t] = (t < length) ? c : 0x00;
    }

    return guid;
}

void BaseRepository::OpenDatabase()
{
    int resultCode = sqlite3_open(databaseFilePath.c_str(), &database);
    if (resultCode != SQLITE_OK)
        throw SqlException(sqlite3_errmsg(database));
}

sqlite3_stmt *BaseRepository::PrepareQuery(string query)
{
    sqlite3_stmt *statement;
    int resultCode = sqlite3_prepare_v2(database, query.c_str(), query.size() + 1, &statement, NULL);
    if (resultCode != SQLITE_OK)
        throw SqlException(sqlite3_errmsg(database));

    return statement;
}