#ifndef UDPRESPONSESENDER_H
#define UDPRESPONSESENDER_H

#include "IResponseSender.h"
#include "UdpRequestData.h"
#include <memory>

using namespace std;

class UdpResponseSender;
using UdpResponseSenderPtr = shared_ptr<UdpResponseSender>;

class UdpResponseSender : public IResponseSender
{
    UdpRequestDataPtr m_object;

public:
    UdpResponseSender(UdpRequestDataPtr obj);

    static UdpResponseSenderPtr Create(UdpRequestDataPtr obj)
    {
        return make_shared<UdpResponseSender>(obj);
    }

    void Send(string text) override;
};

#endif // UDPRESPONSESENDER_H
