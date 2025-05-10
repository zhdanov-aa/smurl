#include "HttpRequestTerminator.h"

HttpRequestTerminator::HttpRequestTerminator()
    :HttpRequestHandlerTemplate(nullptr)
{
}

bool HttpRequestTerminator::CanHandle(http::request<http::string_body> &req)
{
    return true;
}

http::response<http::string_body> HttpRequestTerminator::Handle(http::request<http::string_body> &req)
{
    http::response<http::string_body> res;

    res.result(http::status::method_not_allowed);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Метод не поддерживается";

    return res;
}
