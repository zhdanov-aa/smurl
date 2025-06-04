#include "RequestInterpretCommand.h"
#include "HttpRequest.h"
#include "IRequestHandler.h"
#include <IoC.h>

RequestInterpretCommand::RequestInterpretCommand(std::string requestId)
    :m_requestId(requestId)
{
}

void RequestInterpretCommand::Execute()
{
    auto handler = IoC::Resolve<IRequestHandlerPtr>("Endpoint.Request.Handler.Get", m_requestId);

    auto command = handler->HandleRequest();

    command->Execute();
}
