#include "BadRequestHandler.h"
#include "HttpBadRequestCommand.h"

BadRequestHandler::BadRequestHandler(HttpRequestHandlerPtr next)
    :HttpRequestHandler(next)
{

}

bool BadRequestHandler::CanHandle(HttpRequestPtr request)
{
    if(!request->error())
        return false;

    return true;
}

ICommandPtr BadRequestHandler::Handle(HttpRequestPtr request)
{
    return HttpBadRequestCommand::Create(request->socketptr());
}
