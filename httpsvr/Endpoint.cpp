#include "Endpoint.h"
#include "IoC.h"
#include "IOutputCommandStream.h"
#include "IRequestAcceptingObject.h"
#include "DeleteCommand.h"
#include <string>

Endpoint::Endpoint()
{
}

void Endpoint::EventLoop()
{
    while(IoC::Resolve<bool>("Endpoint.Alive.Get"))
    {
        auto requestId = IoC::Resolve<std::string>("Endpoint.Request.Get");

        IoC::Resolve<IRequestAcceptingObjectPtr>(
            "Endpoint.Request.AcceptingObject.Get",
            requestId)->Accept();

        auto stream = IoC::Resolve<IOutputCommandStreamPtr>("Endpoint.OutputCommandStream.Get");

        stream->Write(IoC::Resolve<ICommandPtr>("Endpoint.Request.InterpretCommand.Get", requestId));
        stream->Write(DeleteCommand::Create(
            IoC::Resolve<ICommandPtr>("Endpoint.Request.DeletingObject.Get", requestId)));
    }
}
