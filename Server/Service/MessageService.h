#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <string>
#include <vector>
#include "../ViewModel/MessageViewModel.h"
using namespace std;

class MessageService
{
  public:
    MessageService(MessageRepository *messageRepository, UserRepository *userRepository);

    void AddMessage(string senderName, string recipientName, string body);
    vector<MessageViewModel> GetUnreadMessages(string userName);
    void SetAsRead(string messageId);

  private:
    MessageRepository *messageRepository;
    UserRepository *userRepository;
};

#endif