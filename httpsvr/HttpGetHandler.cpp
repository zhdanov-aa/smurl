#include "HttpGetHandler.h"
#include <stdexcept>

HttpGetHandler::HttpGetHandler(HttpRequestHandlerChainPtr next)
    :HttpRequestHandlerChain(next)
{}

bool HttpGetHandler::CanHandle(http::request<http::string_body> &req)
{
    return (req.method() == http::verb::get);
}

http::response<http::string_body> HttpGetHandler::Handle(http::request<http::string_body> &req)
{
    http::response<http::string_body> res;

    res.result(http::status::permanent_redirect);
    res.set(http::field::location, "https://yandex.ru");
    res.set(http::field::content_type, "text/plain");
    res.body() = "Вы будете перенаправлены на mail.ru";
    res.content_length(res.body().size());
    res.keep_alive(true);

    return res;
}
