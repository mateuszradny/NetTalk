#ifndef CONTACTREPOSITORY_H
#define CONTACTREPOSITORY_H

#include <string>
#include <vector>
#include "../Model/Contact.h"
#include "BaseRepository.h"
using namespace std;

class ContactRepository : public BaseRepository
{
  public:
    ContactRepository(string databaseFilePath);

    void AddIfNotExists(Contact contact);
    vector<Contact> GetByUserName(string userName);
    void Remove(Contact contact);

  private:
    vector<Contact> ExecuteSelectQuery(string query);
    string GetDeleteCommand(Contact contact);
    string GetInsertCommand(Contact contact);
    string GetSelectByUserNameQuery(string userName);
    string GetSelectByUserNameAndContactNameQuery(string userName, string contactName);
};

#endif