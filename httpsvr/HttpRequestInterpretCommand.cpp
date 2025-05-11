#include "HttpRequestInterpretCommand.h"
#include "HttpRequest.h"
#include "IHttpRequestHandler.h"
#include <IoC.h>

namespace http = boost::beast::http;

HttpRequestInterpretCommand::HttpRequestInterpretCommand(IRequestPtr client)
    :m_client(client)
{}


void HttpRequestInterpretCommand::Execute()
{
    HttpRequestPtr client = std::dynamic_pointer_cast<HttpRequest>(m_client);

    if (!client->error())
    {
        http::response<http::string_body> res;
        res = IoC::Resolve<IHttpRequestHandlerPtr>(
                  "HttpRequestHandler.New")->HandleRequest(client->request());

        http::write(client->socket(), res);
    }
    else
    {
        // Формируем ответ об ошибке
        http::response<http::string_body> res;
        res.result(http::status::bad_request);
        res.set(http::field::content_type, "text/plain");
        res.body() = "Ошибка чтения запроса";
        res.content_length(res.body().size());
        res.keep_alive(true);

        // Отправляем ответ об ошибке
        http::write(client->socket(), res);
    }
}
