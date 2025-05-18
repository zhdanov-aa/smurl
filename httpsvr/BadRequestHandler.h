#ifndef BADREQUESTHANDLER_H
#define BADREQUESTHANDLER_H

#include "RequestHandler.h"
#include "HttpRequest.h"
#include <memory>

class BadRequestHandler;
using BadRequestHandlerPtr = std::shared_ptr<BadRequestHandler>;

class BadRequestHandler : public RequestHandler
{
    HttpRequestPtr m_request;

public:
    BadRequestHandler(HttpRequestPtr request);

    static BadRequestHandlerPtr Create(HttpRequestPtr request)
    {
        return std::make_shared<BadRequestHandler>(request);
    }

    bool CanHandle() override;
    ICommandPtr Handle() override;
};

#endif // BADREQUESTHANDLER_H
