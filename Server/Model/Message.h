#ifndef MESSAGE_H
#define MESSAGE_H

#include <ctime>
#include <string>
using namespace std;

class Message
{
  public:
    string Id;
    string SenderName;
    string RecipientName;
    time_t PostDate;
    string Body;
    bool IsRead;
};

#endif