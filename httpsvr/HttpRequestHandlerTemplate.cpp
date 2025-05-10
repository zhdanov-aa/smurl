#include "HttpRequestHandlerTemplate.h"
#include <stdexcept>

HttpRequestHandlerTemplate::HttpRequestHandlerTemplate(HttpRequestHandlerTemplatePtr next)
    :m_Successer(next)
{
}

http::response<boost::beast::http::string_body> HttpRequestHandlerTemplate::HandleRequest(http::request<http::string_body> &req)
{
    if (CanHandle(req))
    {
        return Handle(req);
    }
    else if (m_Successer != nullptr)
    {
        return m_Successer->HandleRequest(req);
    }
    else
    {
        throw std::runtime_error("HttpRequestHandlerTemplate::HandleRequest(): successer is nullptr");
    }
}
