#include "HttpRequestInterpretCommand.h"
#include "HttpRequest.h"
#include "IHttpRequestHandler.h"
#include <IoC.h>

HttpRequestInterpretCommand::HttpRequestInterpretCommand(HttpRequestPtr request)
    :m_request(request)
{}

void HttpRequestInterpretCommand::Execute()
{
    IoC::Resolve<IHttpRequestHandlerPtr>(
        "HttpRequestHandler.New")->HandleRequest(m_request);
}
