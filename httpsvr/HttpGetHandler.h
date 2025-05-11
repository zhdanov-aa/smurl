#ifndef HTTPGETHANDLER_H
#define HTTPGETHANDLER_H

#include "HttpRequestHandlerChain.h"
#include <memory>

class HttpGetHandler;
using HttpGetHandlerPtr = std::shared_ptr<HttpGetHandler>;

class HttpGetHandler : public HttpRequestHandlerChain
{
public:
    HttpGetHandler(HttpRequestHandlerChainPtr next);

    static HttpGetHandlerPtr Create(HttpRequestHandlerChainPtr next) { return std::make_shared<HttpGetHandler>(next); }

    bool CanHandle(http::request<http::string_body> &req) override;
    http::response<http::string_body> Handle(http::request<http::string_body> &req) override;
};

#endif // HTTPGETHANDLER_H
