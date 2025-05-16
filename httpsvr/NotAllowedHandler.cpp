#include "NotAllowedHandler.h"
#include "HttpNotAllowedCommand.h"

namespace http = boost::beast::http;

NotAllowedHandler::NotAllowedHandler()
    :HttpRequestHandler(nullptr)
{
}

bool NotAllowedHandler::CanHandle(HttpRequestPtr request)
{
    return true;
}

ICommandPtr NotAllowedHandler::Handle(HttpRequestPtr request)
{
    return HttpNotAllowedCommand::Create(request->socketptr());
}
