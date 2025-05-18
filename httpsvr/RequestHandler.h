#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "IRequestHandler.h"
#include <memory>

class RequestHandler;
using RequestHandlerPtr = std::shared_ptr<RequestHandler>;

class RequestHandler: public IRequestHandler
{
    IRequestHandlerPtr m_Successer;

protected:
    virtual bool CanHandle() = 0;
    virtual ICommandPtr Handle() = 0;

public:
    RequestHandler();
    RequestHandlerPtr SetNext(RequestHandlerPtr next);

    ICommandPtr HandleRequest() override;
};

#endif // REQUESTHANDLER_H
