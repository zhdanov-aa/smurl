#ifndef UDPREDIRECTOR_H
#define UDPREDIRECTOR_H

#include "IRedirector.h"
#include <memory>

using namespace std;

class UdpRedirector;
using UdpRedirectorPtr = shared_ptr<UdpRedirector>;

class UdpRedirector : public IRedirector
{
    IJsonObjectPtr m_jsonObject;

public:
    UdpRedirector(IJsonObjectPtr jsonObject);

    static UdpRedirectorPtr Create(IJsonObjectPtr jsonObject)
    {
        return make_shared<UdpRedirector>(jsonObject);
    }

    std::string GetLocation() override;
};

#endif // UDPREDIRECTOR_H
