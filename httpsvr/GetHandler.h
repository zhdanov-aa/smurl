#ifndef GETHANDLER_H
#define GETHANDLER_H

#include "RequestHandler.h"
#include "HttpRequest.h"
#include <memory>


class GetHandler;
using GetHandlerPtr = std::shared_ptr<GetHandler>;

class GetHandler : public RequestHandler
{
    HttpRequestPtr m_request;

public:
    GetHandler(HttpRequestPtr request);

    static GetHandlerPtr Create(HttpRequestPtr request)
    {
        return std::make_shared<GetHandler>(request);
    }

    bool CanHandle() override;
    ICommandPtr Handle() override;
};

#endif // GETHANDLER_H
