#include "RegistrationResponse.h"

RegistrationResponse::RegistrationResponse(RegistrationResult result)
{
    this->result = result;
}

RegistrationResult RegistrationResponse::GetResult() const
{
    return this->result;
}

ResponseType RegistrationResponse::GetResponseType() const
{
    return ResponseType::RegistrationResult;
}

string RegistrationResponse::ToString() const
{
    ostringstream stream;
    stream << (int)GetResponseType() << ' ' << (int)GetResult();
    return stream.str();
}

RegistrationResponse *RegistrationResponse::Parse(string str)
{
    istringstream stream(str);
    int responseType, result;
    stream >> responseType >> result;

    if ((ResponseType)responseType != ResponseType::RegistrationResult)
        throw "Invalid type of request";

    return new RegistrationResponse((RegistrationResult)result);
}