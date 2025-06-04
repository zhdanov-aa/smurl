#include "RequestHandler.h"
#include <stdexcept>

RequestHandler::RequestHandler()
{
}

RequestHandlerPtr RequestHandler::SetNext(RequestHandlerPtr next)
{
    m_Successer = next;
    return next;
}

ICommandPtr RequestHandler::HandleRequest()
{
    if (CanHandle())
    {
        return Handle();
    }
    else if (m_Successer != nullptr)
    {
        return m_Successer->HandleRequest();
    }
    else
    {
        throw std::runtime_error("HttpRequestHandler::HandleRequest(): successer is nullptr");
    }
}
