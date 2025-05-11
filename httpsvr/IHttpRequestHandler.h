#ifndef IHTTPREQUESTHANDLER_H
#define IHTTPREQUESTHANDLER_H

#include "HttpRequest.h"
#include <memory>

class IHttpRequestHandler
{
public:
    virtual ~IHttpRequestHandler() = default;
    virtual void HandleRequest(HttpRequestPtr request) = 0;
};

using IHttpRequestHandlerPtr = std::shared_ptr<IHttpRequestHandler>;

#endif // IHTTPREQUESTHANDLER_H
