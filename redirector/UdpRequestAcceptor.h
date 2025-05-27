#ifndef UDPREQUESTACCEPTOR_H
#define UDPREQUESTACCEPTOR_H

#include <IMessageQueue.h>
#include <memory>
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>

using namespace std;
using boost::asio::ip::udp;

class UdpRequestAcceptor;
using UdpRequestAcceptorPtr = shared_ptr<UdpRequestAcceptor>;

class UdpRequestAcceptor : public IMessageQueue
{
    boost::asio::io_context m_iocontext;
    udp::socket m_socket;
    udp::endpoint m_endpoint;

public:
    UdpRequestAcceptor(unsigned short port);

    static UdpRequestAcceptorPtr Create(unsigned short port)
    {
        return make_shared<UdpRequestAcceptor>(port);
    }

    string GetMessage() override;
};

#endif // UDPREQUESTACCEPTOR_H
