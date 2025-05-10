#ifndef HTTPGETHANDLER_H
#define HTTPGETHANDLER_H

#include "HttpRequestHandlerTemplate.h"
#include <memory>

class HttpGetHandler;
using HttpGetHandlerPtr = std::shared_ptr<HttpGetHandler>;

class HttpGetHandler : public HttpRequestHandlerTemplate
{
public:
    HttpGetHandler(HttpRequestHandlerTemplatePtr next);

    static HttpGetHandlerPtr Create(HttpRequestHandlerTemplatePtr next) { return std::make_shared<HttpGetHandler>(next); }

    bool CanHandle(http::request<http::string_body> &req) override;
    http::response<http::string_body> Handle(http::request<http::string_body> &req) override;
};

#endif // HTTPGETHANDLER_H
