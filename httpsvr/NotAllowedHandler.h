#ifndef NOTALLOWEDHANDLER_H
#define NOTALLOWEDHANDLER_H

#include "HttpRequestHandler.h"
#include <memory>

class NotAllowedHandler;
using NotAllowedHandlerPtr = std::shared_ptr<NotAllowedHandler>;

class NotAllowedHandler : public HttpRequestHandler
{
public:
    NotAllowedHandler();

    static NotAllowedHandlerPtr Create() { return std::make_shared<NotAllowedHandler>(); }

    bool CanHandle(HttpRequestPtr request) override;
    ICommandPtr Handle(HttpRequestPtr request) override;
};

#endif // NOTALLOWEDHANDLER_H
