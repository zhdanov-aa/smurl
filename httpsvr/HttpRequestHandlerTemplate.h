#ifndef HTTPREQUESTHANDLERTEMPLATE_H
#define HTTPREQUESTHANDLERTEMPLATE_H

#include "IHttpRequestHandler.h"
#include <memory>

class HttpRequestHandlerTemplate;
using HttpRequestHandlerTemplatePtr = std::shared_ptr<HttpRequestHandlerTemplate>;

class HttpRequestHandlerTemplate: public IHttpRequestHandler
{
    IHttpRequestHandlerPtr m_Successer;

protected:
    virtual bool CanHandle(http::request<http::string_body> &req) = 0;
    virtual http::response<http::string_body> Handle(http::request<http::string_body> &req) = 0;

public:
    HttpRequestHandlerTemplate(HttpRequestHandlerTemplatePtr next);

    http::response<http::string_body> HandleRequest(http::request<http::string_body> &req) override;
};

#endif // HTTPREQUESTHANDLERTEMPLATE_H
