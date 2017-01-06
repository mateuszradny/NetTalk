#ifndef MESSAGEVIEWMODEL_H
#define MESSAGEVIEWMODEL_H

class MessageViewModel
{
public:
  string Id;
  string SenderName;
  time_t PostDate;
  string Body;
};

#endif