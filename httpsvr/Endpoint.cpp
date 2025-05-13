#include <string>
//#include <iostream>

#include "Endpoint.h"
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
        std::string requestId = IoC::Resolve<std::string>("Endpoint.Request.New");

        IoC::Resolve<ICommandPtr>("Endpoint.Request.AcceptCommand.New", requestId)->Execute();

        IoC::Resolve<IOutputCommandStreamPtr>("Endpoint.OutputCommandStream.Get")->Write(
            IoC::Resolve<ICommandPtr>("Endpoint.Request.InterpretCommand.New", requestId)
            );
    }
}
