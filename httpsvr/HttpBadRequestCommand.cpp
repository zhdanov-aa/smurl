#include "HttpBadRequestCommand.h"
//#include <boost/asio.hpp>
//#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>

namespace http = boost::beast::http;

HttpBadRequestCommand::HttpBadRequestCommand(HttpSocketPtr socket)
    : m_socket(socket)
{

}

void HttpBadRequestCommand::Execute()
{
    // Формируем ответ об ошибке
    http::response<http::string_body> res;
    res.result(http::status::bad_request);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Ошибка чтения запроса";
    res.content_length(res.body().size());
    res.keep_alive(true);

    // Отправляем ответ об ошибке
    http::write(*m_socket, res);
}
