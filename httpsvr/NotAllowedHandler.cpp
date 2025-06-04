#include "NotAllowedHandler.h"
#include "SendNotAllowedCommand.h"

namespace http = boost::beast::http;

NotAllowedHandler::NotAllowedHandler(HttpRequestPtr request)
    :m_request(request)
{
}

bool NotAllowedHandler::CanHandle()
{
    return true;
}

ICommandPtr NotAllowedHandler::Handle()
{
    return SendNotAllowedCommand::Create(m_request->socketptr());
}
