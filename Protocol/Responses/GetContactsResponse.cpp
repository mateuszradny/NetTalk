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

    int responseType = (int)GetResponseType();
    stream.write((char *)&responseType, sizeof(responseType));

    int count = contacts.size();
    stream.write((char *)&count, sizeof(count));

    for (int i = 0; i < count; i++)
    {
        int length = contacts[i].ContactName.size();
        stream.write((char *)&length, sizeof(length));
        stream.write(&contacts[i].ContactName[0], length);
        stream.write((char *)&contacts[i].IsOnline, sizeof(contacts[i].IsOnline));
    }

    return stream.str();
}