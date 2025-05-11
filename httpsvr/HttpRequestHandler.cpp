#include "HttpRequestHandler.h"
#include <stdexcept>

HttpRequestHandler::HttpRequestHandler(HttpRequestHandlerPtr next)
    :m_Successer(next)
{
}

void HttpRequestHandler::HandleRequest(HttpRequestPtr request)
{
    if (CanHandle(request))
    {
        Handle(request);
    }
    else if (m_Successer != nullptr)
    {
        m_Successer->HandleRequest(request);
    }
    else
    {
        throw std::runtime_error("HttpRequestHandler::HandleRequest(): successer is nullptr");
    }
}
