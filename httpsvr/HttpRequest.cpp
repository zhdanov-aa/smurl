#include "HttpRequest.h"

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
    // Закрываем соединение
    if (m_socket != nullptr)
    {
        boost::beast::error_code ec;
        m_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    }
}

