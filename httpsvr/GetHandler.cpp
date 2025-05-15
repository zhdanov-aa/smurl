#include "GetHandler.h"
#include <stdexcept>

namespace http = boost::beast::http;

GetHandler::GetHandler(HttpRequestHandlerPtr next)
    :HttpRequestHandler(next)
{}

bool GetHandler::CanHandle(HttpRequestPtr request)
{
    return (request->request().method() == http::verb::get);
}

void GetHandler::Handle(HttpRequestPtr request)
{
    http::response<http::string_body> res;

    res.result(http::status::permanent_redirect);
    res.set(http::field::location, "https://mail.ru");
    res.set(http::field::content_type, "text/plain");
    res.body() = "Вы будете перенаправлены на mail.ru";
    res.content_length(res.body().size());
    res.keep_alive(true);

    http::write(request->socket(), res);
}
