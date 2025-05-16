#ifndef IHTTPREQUESTHANDLER_H
#define IHTTPREQUESTHANDLER_H

#include "HttpRequest.h"
#include "ICommand.h"
#include <memory>

class IHttpRequestHandler
{
public:
    virtual ~IHttpRequestHandler() = default;
    virtual ICommandPtr HandleRequest(HttpRequestPtr request) = 0;
};

using IHttpRequestHandlerPtr = std::shared_ptr<IHttpRequestHandler>;

#endif // IHTTPREQUESTHANDLER_H
