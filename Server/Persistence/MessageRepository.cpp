#include "MessageRepository.h"
#include "../ExternalLibraries/sqlite3.h"

#include <iostream>

MessageRepository::MessageRepository(string databaseFilePath) : BaseRepository(databaseFilePath)
{
}

void MessageRepository::Add(Message message)
{
    message.Id = NewGuid();

    OpenDatabase();
    string command = GetInsertCommand(message);
    ExecuteNonQuery(command);
    CloseDatabase();
}

vector<Message> MessageRepository::GetUnreadMessagesByRecipientName(string recipientName)
{
    OpenDatabase();
    string query = GetSelectByRecipientNameWhereIsReadEqualsFalseQuery(recipientName);
    vector<Message> messages = ExecuteSelectQuery(query);
    CloseDatabase();

    return messages;
}

void MessageRepository::SetAsRead(string messageId)
{
    OpenDatabase();
    string command = GetUpdateCommandWhichSetIsReadToTrue(messageId);
    ExecuteNonQuery(command);
    CloseDatabase();
}

vector<Message> MessageRepository::ExecuteSelectQuery(string query)
{
    vector<Message> messages;

    sqlite3_stmt *statement = PrepareQuery(query);
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Message message;
        message.Id = (char *)sqlite3_column_text(statement, 0);
        message.SenderName = (char *)sqlite3_column_text(statement, 1);
        message.RecipientName = (char *)sqlite3_column_text(statement, 2);
        message.PostDate = (long long)sqlite3_column_int64(statement, 3);
        message.Body = (char *)sqlite3_column_text(statement, 4);
        message.IsRead = (bool)sqlite3_column_int(statement, 5);

        messages.push_back(message);
    }

    return messages;
}

string MessageRepository::GetInsertCommand(Message message)
{
    string command;

    command.append("INSERT INTO Messages (Id, SenderName, RecipientName, PostDate, Body, IsRead) VALUES('");
    command.append(message.Id);
    command.append("', '");
    command.append(message.SenderName);
    command.append("', '");
    command.append(message.RecipientName);
    command.append("', '");
    command.append(to_string((long long)message.PostDate));
    command.append("', '");
    command.append(message.Body);
    command.append("', '");
    command.append(to_string((int)message.IsRead));
    command.append("');");

    return command;
}

string MessageRepository::GetSelectByRecipientNameWhereIsReadEqualsFalseQuery(string recipientName)
{
    string query;

    query.append("SELECT Id, SenderName, RecipientName, PostDate, Body, IsRead FROM Messages WHERE IsRead='0' AND RecipientName='");
    query.append(recipientName);
    query.append("';");

    return query;
}

string MessageRepository::GetUpdateCommandWhichSetIsReadToTrue(string messageId)
{
    string command;

    command.append("UPDATE Messages SET IsRead='1' WHERE Id='");
    command.append(messageId);
    command.append("'");

    return command;
}