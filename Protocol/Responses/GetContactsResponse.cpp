#include "GetContactsResponse.h"

GetContactsResponse::GetContactsResponse(vector<ContactViewModel> contacts)
{
    this->contacts = contacts;
}

vector<ContactViewModel> GetContactsResponse::GetContacts() const
{
    return this->contacts;
}

ResponseType GetContactsResponse::GetResponseType() const
{
    return ResponseType::GetContacts;
}

string GetContactsResponse::ToString() const
{
    ostringstream stream;
    stream << (int)GetResponseType() << ' ' << contacts.size();
    for (int i = 0; i < contacts.size(); i++)
        stream << ' ' << contacts[i].ContactName << ' ' << contacts[i].IsOnline;

    return stream.str();
}

GetContactsResponse *GetContactsResponse::Parse(string str)
{
    istringstream stream(str);
    int responseType, contactCount;
    stream >> responseType >> contactCount;

    if ((ResponseType)responseType != ResponseType::GetContacts)
        throw "Invalid type of request";

    vector<ContactViewModel> contacts;
    for (int i = 0; i < contactCount; i++)
    {
        ContactViewModel contact;
        stream >> contact.ContactName >> contact.IsOnline;

        contacts.push_back(contact);
    }

    return new GetContactsResponse(contacts);
}