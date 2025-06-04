#include "SendNotFoundCommand.h"
#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

SendNotFoundCommand::SendNotFoundCommand(HttpSocketPtr socket)
    :m_socket(socket)
{
}

void SendNotFoundCommand::Execute()
{
    http::response<http::string_body> res;

    res.result(http::status::not_found);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Not found";

    http::write(*m_socket, res);
}
