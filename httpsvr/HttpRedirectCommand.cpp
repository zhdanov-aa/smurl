#include "HttpRedirectCommand.h"
#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

HttpRedirectCommand::HttpRedirectCommand(HttpSocketPtr socket, std::string location)
    :m_socket(socket), m_location(location)
{
}

void HttpRedirectCommand::Execute()
{
    http::response<http::string_body> res;

    res.result(http::status::permanent_redirect);
    res.set(http::field::location, m_location);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Вы будете перенаправлены на mail.ru";
    res.content_length(res.body().size());
    res.keep_alive(true);

    http::write(*m_socket, res);
}
