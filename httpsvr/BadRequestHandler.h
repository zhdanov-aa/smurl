#ifndef BADREQUESTHANDLER_H
#define BADREQUESTHANDLER_H

#include "HttpRequestHandler.h"
#include <memory>

class BadRequestHandler;
using BadRequestHandlerPtr = std::shared_ptr<BadRequestHandler>;

class BadRequestHandler : public HttpRequestHandler
{
public:
    BadRequestHandler(HttpRequestHandlerPtr next);

    static BadRequestHandlerPtr Create(HttpRequestHandlerPtr next) { return std::make_shared<BadRequestHandler>(next); }

    bool CanHandle(HttpRequestPtr request) override;
    ICommandPtr Handle(HttpRequestPtr request) override;
};

#endif // BADREQUESTHANDLER_H
