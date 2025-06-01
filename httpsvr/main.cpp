#include "Endpoint.h"
#include <IException.h>
#include <IoC.h>
#include <ICommand.h>
#include "GetHandler.h"
#include "NotAllowedHandler.h"
#include "BadRequestHandler.h"
#include "HttpRequest.h"

#include "RequestInterpretCommand.h"
#include "DeleteHttpRequestCommand.h"
#include "MacroCommand.h"
#include "PrintJsonObjectCommand.h"

#include "IOutputCommandStream.h"
#include "DirectCommandExecutor.h"

#include "IJsonObject.h"

#include "RuntimeError.h"

#include "HttpRequestAcceptor.h"
#include "HttpRequestJsonObject.h"

#include "UdpRedirector.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <map>
#include <string>
#include <vector>
#include <iostream>

void InitIoC();

int main()
{
    InitIoC();

    Endpoint svr(
        HttpRequestAcceptor::Create(8080),
        DirectCommandExecutor::Create()
        );

    try
    {
        svr.EventLoop();
    }
    catch(IException *e)
    {
        std::cerr << "Ошибка: " << e->WhatHappened() << std::endl;
        delete e;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void InitIoC()
{
    auto requests = std::make_shared<std::map<std::string, HttpRequestPtr>>();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Http.Request.New",
        RESOLVER([requests](HttpRequestPtr nr){
            std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
            (*requests)[requestId] = nr;
            return requestId;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Message.InterpretCommand.Get",
        RESOLVER([requests](std::string requestId)-> ICommandPtr {
            std::vector<ICommandPtr> commands =
                {
                    PrintJsonObjectCommand::Create(HttpRequestJsonObject::Create((*requests)[requestId])),
                    RequestInterpretCommand::Create(requestId),
                    DeleteHttpRequestCommand::Create(requests, requestId)
                };
            return MacroCommand::Create(commands);
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.JsonObject.Get",
        RESOLVER([requests](std::string requestId){
            IJsonObjectPtr jsonObject = HttpRequestJsonObject::Create(
                (*requests)[requestId]);
            return jsonObject;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.Handler.Get",
        RESOLVER([requests](std::string requestId) -> IRequestHandlerPtr {
            RequestHandlerPtr handler = BadRequestHandler::Create((*requests)[requestId]);
            handler->SetNext(GetHandler::Create((*requests)[requestId]))
                ->SetNext(NotAllowedHandler::Create((*requests)[requestId]));
            return handler;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Http.Redirector.Get",
        RESOLVER([](IJsonObjectPtr jsonObject) -> IRedirectorPtr {
            // return MonolithRedirector::Create(jsonObject);
            return UdpRedirector::Create(jsonObject);
        }))->Execute();

}
