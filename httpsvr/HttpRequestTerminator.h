#ifndef HTTPREQUESTTERMINATOR_H
#define HTTPREQUESTTERMINATOR_H

#include "HttpRequestHandlerChain.h"
#include <memory>

class HttpRequestTerminator;
using HttpRequestTerminatorPtr = std::shared_ptr<HttpRequestTerminator>;

class HttpRequestTerminator : public HttpRequestHandlerChain
{
public:
    HttpRequestTerminator();

    static HttpRequestTerminatorPtr Create() { return std::make_shared<HttpRequestTerminator>(); }

    bool CanHandle(http::request<http::string_body> &req) override;
    http::response<http::string_body> Handle(http::request<http::string_body> &req) override;
};

#endif // HTTPREQUESTTERMINATOR_H
