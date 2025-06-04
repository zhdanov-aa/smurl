#include "SendNotAllowedCommand.h"
#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

SendNotAllowedCommand::SendNotAllowedCommand(HttpSocketPtr socket)
    :m_socket(socket)
{
}

void SendNotAllowedCommand::Execute()
{
    http::response<http::string_body> res;

    res.result(http::status::method_not_allowed);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Method not allowed";

    http::write(*m_socket, res);
}
