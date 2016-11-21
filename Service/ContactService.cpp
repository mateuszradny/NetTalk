#include "ContactService.h"

ContactService::ContactService(UserRepository *userRepository, ContactRepository *contactRepository, AuthService *authService)
{
    if (userRepository == nullptr)
        throw "User repository is null";

    if (contactRepository == nullptr)
        throw "Contact repository is null";

    if (authService == nullptr)
        throw "Auth service is null";

    this->authService = authService;
    this->userRepository = userRepository;
    this->contactRepository = contactRepository;
}

void ContactService::AddContact(string userName, string contactName)
{
    if (!this->userRepository->Exists(contactName))
        throw UserNotFoundException(contactName);

    Contact contact;
    contact.UserName = userName;
    contact.ContactName = contactName;

    this->contactRepository->AddIfNotExists(contact);
}

vector<ContactViewModel> ContactService::GetContactsByUserName(string userName)
{
    vector<Contact> contacts = this->contactRepository->GetByUserName(userName);
    vector<ContactViewModel> result;

    for (int i = 0; i < contacts.size(); i++)
    {
        ContactViewModel contact;
        contact.ContactName = contacts[i].ContactName;
        contact.IsOnline = this->authService->IsOnline(contacts[i].ContactName);

        result.push_back(contact);
    }

    return result;
}

void ContactService::RemoveContact(string userName, string contactName)
{
    Contact contact;
    contact.UserName = userName;
    contact.ContactName = contactName;

    this->contactRepository->Remove(contact);
}