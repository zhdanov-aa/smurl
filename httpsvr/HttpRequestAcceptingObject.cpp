#include "HttpRequestAcceptingObject.h"
#include "InvalidArgument.h"

HttpRequestAcceptingObject::HttpRequestAcceptingObject(HttpRequestPtr request)
    : m_request(request)
{

}

void HttpRequestAcceptingObject::Accept()
{
    if (m_request == nullptr)
        throw new InvalidArgument("HttpRequestAcceptingObject::Accept(): request is nullptr");

    // Принимаем новое соединение
    m_request->acceptor().accept(m_request->socket());

    // Читаем запрос с проверкой
    boost::beast::http::read(
        m_request->socket(),
        m_request->buffer(),
        m_request->request(),
        m_request->error());

}
