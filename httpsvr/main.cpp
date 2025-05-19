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

#include "IRequestAcceptingObject.h"
#include "IJsonObject.h"

#include "RuntimeError.h"

#include "HttpRequestAcceptingObject.h"
#include "HttpRequestJsonObject.h"

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

    try
    {
        Endpoint svr;
        svr.EventLoop();
    }
    catch(std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return EXIT_FAILURE;
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
        "Endpoint.Alive.Get",
        RESOLVER([](){
            return true;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.New",
        RESOLVER([requests](){
            static boost::asio::io_context ioc;
            static std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor =
                std::make_shared<boost::asio::ip::tcp::acceptor>(
                    ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8084));
            std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
            (*requests)[requestId] = std::make_shared<HttpRequest>(acceptor);
            return requestId;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.AcceptingObject.Get",
        RESOLVER([requests](std::string requestId) -> IRequestAcceptingObjectPtr {
            IRequestAcceptingObjectPtr acceptingObject = HttpRequestAcceptingObject::Create(
                (*requests)[requestId]);
            return acceptingObject;
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
        "Endpoint.OutputCommandStream.Get",
        RESOLVER([]() -> IOutputCommandStreamPtr {
            return DirectCommandExecutor::Create();
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.InterpretCommand.Get",
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
        RESOLVER([](){
            throw new RuntimeError("Http.Redirector.Get not resolved");
        }))->Execute();
}
