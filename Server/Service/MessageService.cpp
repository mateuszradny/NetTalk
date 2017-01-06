#include "MessageService.h"

MessageService::MessageService(MessageRepository *messageRepository, UserRepository *userRepository)
{
    if (messageRepository == nullptr)
        throw "Message repository is null";

    this->messageRepository = messageRepository;
    this->userRepository = userRepository;
}

void MessageService::AddMessage(string senderName, string recipientName, string body)
{
    if (!this->userRepository->Exists(recipientName))
        throw UserNotFoundException(recipientName);

    Message message;
    message.SenderName = senderName;
    message.RecipientName = recipientName;
    message.PostDate = time(nullptr);
    message.Body = body;
    message.IsRead = false;

    messageRepository->Add(message);
}

vector<MessageViewModel> MessageService::GetUnreadMessages(string userName)
{
    vector<Message> unreadMessages = messageRepository->GetUnreadMessagesByRecipientName(userName);
    vector<MessageViewModel> messages;

    for (int i = 0; i < unreadMessages.size(); i++)
    {
        MessageViewModel message;
        message.Id = unreadMessages[i].Id;
        message.SenderName = unreadMessages[i].SenderName;
        message.PostDate = unreadMessages[i].PostDate;
        message.Body = unreadMessages[i].Body;

        messages.push_back(message);
    }

    return messages;
}

void MessageService::SetAsRead(string messageId)
{
    messageRepository->SetAsRead(messageId);
}