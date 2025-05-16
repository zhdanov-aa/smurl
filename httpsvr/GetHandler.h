#ifndef GETHANDLER_H
#define GETHANDLER_H

#include "HttpRequestHandler.h"
#include <memory>

class GetHandler;
using GetHandlerPtr = std::shared_ptr<GetHandler>;

class GetHandler : public HttpRequestHandler
{
public:
    GetHandler(HttpRequestHandlerPtr next);

    static GetHandlerPtr Create(HttpRequestHandlerPtr next) { return std::make_shared<GetHandler>(next); }

    bool CanHandle(HttpRequestPtr request) override;
    ICommandPtr Handle(HttpRequestPtr request) override;
};

#endif // GETHANDLER_H
