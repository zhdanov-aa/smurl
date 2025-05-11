#include "HttpServer.h"
#include <string>
#include <IoC.h>
#include "IHttpRequestHandler.h"
#include "IClient.h"
#include "HttpRequestInterpretCommand.h"
#include <IOutputCommandStream.h>

HttpServer::HttpServer()
{
}

void HttpServer::EventLoop()
{
    while(IoC::Resolve<bool>("Server.Alive.Get"))
    {
        auto client = IoC::Resolve<IHttpClientPtr>("Client.New");

        client->Accept();

        IoC::Resolve<IOutputCommandStreamPtr>("Server.OutputCommandStream.Get")->Write(
            IoC::Resolve<ICommandPtr>("Client.RequestInterpretCommand.New", client));
    }
}
