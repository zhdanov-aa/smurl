#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include "IHttpRequestHandler.h"
#include <memory>

class HttpRequestHandler;
using HttpRequestHandlerPtr = std::shared_ptr<HttpRequestHandler>;

class HttpRequestHandler: public IHttpRequestHandler
{
    IHttpRequestHandlerPtr m_Successer;

protected:
    virtual bool CanHandle(HttpRequestPtr request) = 0;
    virtual ICommandPtr Handle(HttpRequestPtr request) = 0;

public:
    HttpRequestHandler(HttpRequestHandlerPtr next);

    ICommandPtr HandleRequest(HttpRequestPtr request) override;
};

#endif // HTTPREQUESTHANDLER_H
