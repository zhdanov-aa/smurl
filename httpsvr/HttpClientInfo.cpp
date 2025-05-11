#include "HttpClientInfo.h"

HttpClientInfo::HttpClientInfo(std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor)
    :m_acceptor(acceptor)
{
    m_socket = std::make_shared<boost::asio::ip::tcp::socket>(m_acceptor->get_executor());
}

HttpClientInfo::~HttpClientInfo()
{
    // Закрываем соединение
    if (m_socket != nullptr)
    {
        boost::beast::error_code ec;
        m_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    }
}

void HttpClientInfo::Accept()
{
    // Принимаем новое соединение
    m_acceptor->accept(*m_socket);

    // Читаем запрос с проверкой
    boost::beast::http::read(*m_socket, m_buffer, m_request, m_error);
}
