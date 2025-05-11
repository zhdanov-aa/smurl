#include "BadRequestHandler.h"

namespace http = boost::beast::http;

BadRequestHandler::BadRequestHandler(HttpRequestHandlerPtr next)
    :HttpRequestHandler(next)
{

}

bool BadRequestHandler::CanHandle(HttpRequestPtr request)
{
    if(!request->error())
        return false;

    return true;
}

void BadRequestHandler::Handle(HttpRequestPtr request)
{
    // Формируем ответ об ошибке
    http::response<http::string_body> res;
    res.result(http::status::bad_request);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Ошибка чтения запроса";
    res.content_length(res.body().size());
    res.keep_alive(true);

    // Отправляем ответ об ошибке
    http::write(request->socket(), res);
}
