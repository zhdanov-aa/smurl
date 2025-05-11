#ifndef HTTPREQUESTHANDLERCHAIN_H
#define HTTPREQUESTHANDLERCHAIN_H

#include "IHttpRequestHandler.h"
#include <memory>

class HttpRequestHandlerChain;
using HttpRequestHandlerChainPtr = std::shared_ptr<HttpRequestHandlerChain>;

class HttpRequestHandlerChain: public IHttpRequestHandler
{
    IHttpRequestHandlerPtr m_Successer;

protected:
    virtual bool CanHandle(http::request<http::string_body> &req) = 0;
    virtual http::response<http::string_body> Handle(http::request<http::string_body> &req) = 0;

public:
    HttpRequestHandlerChain(HttpRequestHandlerChainPtr next);

    http::response<http::string_body> HandleRequest(http::request<http::string_body> &req) override;
};

#endif // HTTPREQUESTHANDLERCHAIN_H
