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

    int responseType = (int)GetResponseType();
    stream.write((char *)&responseType, sizeof(responseType));
    stream.write((char *)&result, sizeof(result));

    return stream.str();
}