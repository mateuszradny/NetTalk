#include "AddContactResponse.h"

AddContactResponse::AddContactResponse(AddContactResult result)
{
    this->result = result;
}

AddContactResult AddContactResponse::GetResult() const
{
    return this->result;
}

ResponseType AddContactResponse::GetResponseType() const
{
    return ResponseType::AddContact;
}

string AddContactResponse::ToString() const
{
    ostringstream stream;
    stream << (int)GetResponseType() << ' ' << (int)GetResult();
    return stream.str();
}

AddContactResponse *AddContactResponse::Parse(string str)
{
    istringstream stream(str);
    int responseType, result;
    stream >> responseType >> result;

    if ((ResponseType)responseType != ResponseType::AddContact)
        throw "Invalid type of request";

    return new AddContactResponse((AddContactResult)result);
}