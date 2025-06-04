#ifndef NOTALLOWEDHANDLER_H
#define NOTALLOWEDHANDLER_H

#include "RequestHandler.h"
#include "HttpRequest.h"
#include <memory>

class NotAllowedHandler;
using NotAllowedHandlerPtr = std::shared_ptr<NotAllowedHandler>;

class NotAllowedHandler : public RequestHandler
{
    HttpRequestPtr m_request;

public:
    NotAllowedHandler(HttpRequestPtr request);

    static NotAllowedHandlerPtr Create(HttpRequestPtr request)
    {
        return std::make_shared<NotAllowedHandler>(request);
    }

    bool CanHandle() override;
    ICommandPtr Handle() override;
};

#endif // NOTALLOWEDHANDLER_H
