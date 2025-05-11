#include "Endpoint.h"
#include <string>
#include <IoC.h>
#include "IHttpRequestHandler.h"
#include "IRequest.h"
#include "HttpRequestInterpretCommand.h"
#include <IOutputCommandStream.h>

Endpoint::Endpoint()
{
}

void Endpoint::EventLoop()
{
    while(IoC::Resolve<bool>("Endpoint.Alive.Get"))
    {
        auto request = IoC::Resolve<IRequestPtr>("Endpoint.Request.New");

        request->Accept();

        IoC::Resolve<IOutputCommandStreamPtr>("Endpoint.OutputCommandStream.Get")->Write(
            IoC::Resolve<ICommandPtr>("Endpoint.RequestInterpretCommand.New", request));
    }
}
