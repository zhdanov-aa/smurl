#include "GetHandler.h"
#include "HttpRedirectCommand.h"
#include <stdexcept>

namespace http = boost::beast::http;

GetHandler::GetHandler(HttpRequestHandlerPtr next)
    :HttpRequestHandler(next)
{}

bool GetHandler::CanHandle(HttpRequestPtr request)
{
    return (request->request().method() == http::verb::get);
}

ICommandPtr GetHandler::Handle(HttpRequestPtr request)
{
    return HttpRedirectCommand::Create(request->socketptr(), "https://mail.ru");
}
