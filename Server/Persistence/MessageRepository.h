#ifndef MESSAGEREPOSITORY_H
#define MESSAGEREPOSITORY_H

#include <string>
#include <vector>
#include "../Model/Message.h"
#include "BaseRepository.h"
using namespace std;

class MessageRepository : public BaseRepository
{
public:
  MessageRepository(string databaseFilePath);

  void Add(Message message);
  vector<Message> GetUnreadMessagesByRecipientName(string recipientName);
  void SetAsRead(string messageId);

private:
  vector<Message> ExecuteSelectQuery(string query);
  string GetInsertCommand(Message message);
  string GetSelectByRecipientNameWhereIsReadEqualsFalseQuery(string recipientName);
  string GetUpdateCommandWhichSetIsReadToTrue(string messageId);
};

#endif