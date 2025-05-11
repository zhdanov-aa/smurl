#include "HttpRequestInterpretCommand.h"
#include "HttpRequest.h"
#include "IHttpRequestHandler.h"
#include <IoC.h>

HttpRequestInterpretCommand::HttpRequestInterpretCommand(IRequestPtr request)
    :m_request(request)
{}

void HttpRequestInterpretCommand::Execute()
{
    HttpRequestPtr httpRequest = std::dynamic_pointer_cast<HttpRequest>(m_request);

    IoC::Resolve<IHttpRequestHandlerPtr>(
        "HttpRequestHandler.New")->HandleRequest(httpRequest);
}
