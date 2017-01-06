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

    int responseType = (int)GetResponseType();
    stream.write((char *)&responseType, sizeof(responseType));

    int result = (int)GetResult();
    stream.write((char *)&result, sizeof(result));

    return stream.str();
}