#ifndef IREQUESTHANDLER_H
#define IREQUESTHANDLER_H

#include "ICommand.h"
#include <memory>

class IRequestHandler
{
public:
    virtual ~IRequestHandler() = default;
    virtual ICommandPtr HandleRequest() = 0;
};

using IRequestHandlerPtr = std::shared_ptr<IRequestHandler>;

#endif // IREQUESTHANDLER_H
