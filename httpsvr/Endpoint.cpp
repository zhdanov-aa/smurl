#include "Endpoint.h"
#include "IoC.h"
#include "IOutputCommandStream.h"
#include "IRequestAcceptingObject.h"
#include <string>

Endpoint::Endpoint()
{
}

void Endpoint::EventLoop()
{
    while(IoC::Resolve<bool>("Endpoint.Alive.Get"))
    {
        auto requestId = IoC::Resolve<std::string>("Endpoint.Request.New");

        IoC::Resolve<IRequestAcceptingObjectPtr>(
            "Endpoint.Request.AcceptingObject.Get", requestId)->Accept();

        IoC::Resolve<IOutputCommandStreamPtr>("Endpoint.OutputCommandStream.Get")->Write(
            IoC::Resolve<ICommandPtr>("Endpoint.Request.InterpretCommand.Get", requestId)
            );
    }
}
