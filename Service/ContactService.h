#ifndef CONTACTSERVICE_H
#define CONTACTSERVICE_H

#include <string>
#include <vector>
#include "../ViewModel/ContactViewModel.h"
using namespace std;

class ContactService
{
public:
  ContactService(UserRepository *userRepository, ContactRepository *contactRepository, AuthService *authService);

  void AddContact(string userName, string contactName);
  vector<ContactViewModel> GetContactsByUserName(string userName);
  void RemoveContact(string userName, string contactName);

private:
  AuthService *authService;
  ContactRepository *contactRepository;
  UserRepository *userRepository;
};

#endif