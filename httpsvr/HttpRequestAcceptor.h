#ifndef HTTPREQUESTACCEPTOR_H
#define HTTPREQUESTACCEPTOR_H

#include <IMessageQueue.h>
#include <memory>
#include <string>
#include <boost/asio.hpp>

using namespace std;

class HttpRequestAcceptor;
using HttpRequestAcceptorPtr = shared_ptr<HttpRequestAcceptor>;

class HttpRequestAcceptor : public IMessageQueue
{
    boost::asio::io_context m_iocontext;
    boost::asio::ip::tcp::acceptor m_acceptor;

public:
    HttpRequestAcceptor(unsigned short port);

    static HttpRequestAcceptorPtr Create(unsigned short port)
    {
        return make_shared<HttpRequestAcceptor>(port);
    }

    string GetMessage() override;
};

#endif // HTTPREQUESTACCEPTOR_H
