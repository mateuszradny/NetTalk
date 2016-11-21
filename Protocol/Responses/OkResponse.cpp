#include "OkResponse.h"

ResponseType OkResponse::GetResponseType() const
{
    return ResponseType::Ok;
}

string OkResponse::ToString() const
{
    ostringstream stream;
    stream << (int)GetResponseType();
    return stream.str();
}