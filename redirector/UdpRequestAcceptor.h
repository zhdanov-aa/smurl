#ifndef UDPREQUESTACCEPTOR_H
#define UDPREQUESTACCEPTOR_H

#include <IMessageQueue.h>
#include <memory>

using namespace std;

class UdpRequestAcceptor;
using UdpRequestAcceptorPtr = shared_ptr<UdpRequestAcceptor>;

class UdpRequestAcceptor : public IMessageQueue
{
public:
    UdpRequestAcceptor(unsigned short port);

    static UdpRequestAcceptorPtr Create(unsigned short port)
    {
        return make_shared<UdpRequestAcceptor>(port);
    }

    string GetMessage() override;
};

#endif // UDPREQUESTACCEPTOR_H
