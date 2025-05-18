#include "BadRequestHandler.h"
#include "SendBadRequestCommand.h"

BadRequestHandler::BadRequestHandler(HttpRequestPtr request)
    :m_request(request)
{

}

bool BadRequestHandler::CanHandle()
{
    if(!m_request->error())
        return false;

    return true;
}

ICommandPtr BadRequestHandler::Handle()
{
    return SendBadRequestCommand::Create(m_request->socketptr());
}
