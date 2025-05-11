#include "NotAllowedHandler.h"

namespace http = boost::beast::http;

NotAllowedHandler::NotAllowedHandler()
    :HttpRequestHandler(nullptr)
{
}

bool NotAllowedHandler::CanHandle(HttpRequestPtr request)
{
    return true;
}

void NotAllowedHandler::Handle(HttpRequestPtr request)
{
    http::response<http::string_body> res;

    res.result(http::status::method_not_allowed);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Метод не поддерживается";

    http::write(request->socket(), res);
}
