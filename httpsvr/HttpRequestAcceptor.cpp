#include "HttpRequestAcceptor.h"
#include "HttpRequest.h"
#include "IoC.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

HttpRequestAcceptor::HttpRequestAcceptor(unsigned short port)
    :m_iocontext(), m_acceptor(m_iocontext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

string HttpRequestAcceptor::GetMessage()
{
    auto request = HttpRequest::Create();

    request->socketptr() = std::make_shared<boost::asio::ip::tcp::socket>(m_iocontext);

    // Принимаем новое соединение
    m_acceptor.accept(request->socket());

    // Читаем запрос с проверкой
    boost::beast::http::read(
        request->socket(),
        request->buffer(),
        request->request(),
        request->error());

    // Создаём новый запрс в системе
    return IoC::Resolve<string>("Http.Request.New", request);
}
