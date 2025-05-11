#ifndef HTTPCLIENTINFO_H
#define HTTPCLIENTINFO_H

#include "IHttpClient.h"
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <memory>

class HttpClientInfo;
using HttpClientInfoPtr = std::shared_ptr<HttpClientInfo>;

class HttpClientInfo: public IHttpClient
{
    std::shared_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;

    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
    boost::beast::flat_buffer m_buffer;
    boost::beast::http::request<boost::beast::http::string_body> m_request;
    boost::beast::error_code m_error;

public:
    HttpClientInfo(std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor);
    ~HttpClientInfo();

    boost::asio::ip::tcp::socket& socket() { return *m_socket; }
    boost::beast::flat_buffer& buffer() { return m_buffer; }
    boost::beast::http::request<boost::beast::http::string_body>& request() { return m_request; }
    boost::beast::error_code& error() { return m_error; }

    void Accept() override;
};

#endif // HTTPCLIENTINFO_H
