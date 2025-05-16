#include "HttpRequestInterpretCommand.h"
#include "HttpRequest.h"
#include "IHttpRequestHandler.h"
#include <IoC.h>

HttpRequestInterpretCommand::HttpRequestInterpretCommand(HttpRequestPtr request)
    :m_request(request)
{}

void HttpRequestInterpretCommand::Execute()
{
    auto handler = IoC::Resolve<IHttpRequestHandlerPtr>("HttpRequestHandler.Get");

    auto command = handler->HandleRequest(m_request);

    command->Execute();
}
