#include "UdpRedirector.h"
#include "RuntimeError.h"

UdpRedirector::UdpRedirector(IJsonObjectPtr jsonObject)
    :m_jsonObject(jsonObject)
{
}


std::string UdpRedirector::GetLocation()
{
    throw new RuntimeError("UdpRedirector::GetLocation() failed");
}
