#include "ContactRepository.h"

ContactRepository::ContactRepository(string databaseFilePath) : BaseRepository(databaseFilePath)
{
}

void ContactRepository::AddIfNotExists(Contact contact)
{
    OpenDatabase();
    string query = GetSelectByUserNameAndContactNameQuery(contact.UserName, contact.ContactName);
    vector<Contact> contacts = ExecuteSelectQuery(query);

    if (contacts.size() == 0)
    {
        string command = GetInsertCommand(contact);
        ExecuteNonQuery(command);
    }

    CloseDatabase();
}

vector<Contact> ContactRepository::GetByUserName(string userName)
{
    OpenDatabase();
    string query = GetSelectByUserNameQuery(userName);
    vector<Contact> contacts = ExecuteSelectQuery(query);
    CloseDatabase();

    return contacts;
}

void ContactRepository::Remove(Contact contact)
{
    OpenDatabase();
    string command = GetDeleteCommand(contact);
    ExecuteNonQuery(command);
    CloseDatabase();
}

vector<Contact> ContactRepository::ExecuteSelectQuery(string query)
{
    vector<Contact> contacts;

    sqlite3_stmt *statement = PrepareQuery(query);
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Contact contact;
        contact.UserName = (char *)sqlite3_column_text(statement, 0);
        contact.ContactName = (char *)sqlite3_column_text(statement, 1);

        contacts.push_back(contact);
    }

    return contacts;
}

string ContactRepository::GetDeleteCommand(Contact contact)
{
    string command;

    command.append("DELETE FROM Contacts WHERE UserName='");
    command.append(contact.UserName);
    command.append("' AND ContactName='");
    command.append(contact.ContactName);
    command.append("');");

    return command;
}

string ContactRepository::GetInsertCommand(Contact contact)
{
    string command;

    command.append("INSERT INTO Contacts (UserName, ContactName) VALUES('");
    command.append(contact.UserName);
    command.append("', '");
    command.append(contact.ContactName);
    command.append("');");

    return command;
}

string ContactRepository::GetSelectByUserNameQuery(string userName)
{
    string query;

    query.append("SELECT UserName, ContactName FROM Contacts WHERE UserName='");
    query.append(userName);
    query.append("';");

    return query;
}

string ContactRepository::GetSelectByUserNameAndContactNameQuery(string userName, string contactName)
{
    string query;

    query.append("SELECT UserName, ContactName FROM Contacts WHERE UserName='");
    query.append(userName);
    query.append("' AND ContactId='");
    query.append(contactName);
    query.append("';");

    return query;
}