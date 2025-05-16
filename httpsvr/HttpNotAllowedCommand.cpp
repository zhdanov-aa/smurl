#include "HttpNotAllowedCommand.h"
#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

HttpNotAllowedCommand::HttpNotAllowedCommand(HttpSocketPtr socket)
    :m_socket(socket)
{
}

void HttpNotAllowedCommand::Execute()
{
    http::response<http::string_body> res;

    res.result(http::status::method_not_allowed);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Метод не поддерживается";

    http::write(*m_socket, res);
}
