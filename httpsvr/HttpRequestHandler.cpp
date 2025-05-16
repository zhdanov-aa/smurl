#include "HttpRequestHandler.h"
#include <stdexcept>

HttpRequestHandler::HttpRequestHandler(HttpRequestHandlerPtr next)
    :m_Successer(next)
{
}

ICommandPtr HttpRequestHandler::HandleRequest(HttpRequestPtr request)
{
    if (CanHandle(request))
    {
        return Handle(request);
    }
    else if (m_Successer != nullptr)
    {
        return m_Successer->HandleRequest(request);
    }
    else
    {
        throw std::runtime_error("HttpRequestHandler::HandleRequest(): successer is nullptr");
    }
}
