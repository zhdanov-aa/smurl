#include "Endpoint.h"
#include <iostream>
#include <IException.h>
#include <IoC.h>
#include <ICommand.h>
#include "GetHandler.h"
#include "NotAllowedHandler.h"
#include "BadRequestHandler.h"
#include "HttpRequest.h"
#include "HttpRequestInterpretCommand.h"
#include "DeleteHttpRequestCommand.h"
#include "MacroCommand.h"
#include "IOutputCommandStream.h"
#include "DirectCommandExecutor.h"
#include "IRequestAcceptingObject.h"
#include "HttpRequestAcceptingObject.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <map>
#include <string>
#include <vector>

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
        make_container(std::function<bool()>([](){

            return true;

        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.New",
        make_container(std::function<std::string()>([requests](){

            static boost::asio::io_context ioc;
            static std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor =
                std::make_shared<boost::asio::ip::tcp::acceptor>(
                    ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8083));
            std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
            (*requests)[requestId] = std::make_shared<HttpRequest>(acceptor);
            return requestId;

        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.AcceptingObject.Get",
        make_container(std::function<IRequestAcceptingObjectPtr(std::string)>([requests](std::string requestId){

            IRequestAcceptingObjectPtr acceptingObject = HttpRequestAcceptingObject::Create(
                (*requests)[requestId]);
            return acceptingObject;

        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.OutputCommandStream.Get",
        make_container(std::function<IOutputCommandStreamPtr()>([](){

            return DirectCommandExecutor::Create();

        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.InterpretCommand.Get",
        make_container(std::function<ICommandPtr(std::string)>([requests](std::string requestId){

            std::vector<ICommandPtr> commands = {
                HttpRequestInterpretCommand::Create((*requests)[requestId]),
                DeleteHttpRequestCommand::Create(requests, requestId)
            };
            return MacroCommand::Create(commands);

        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "HttpRequestHandler.New",
        make_container(std::function<IHttpRequestHandlerPtr()>([](){

            return BadRequestHandler::Create(
                GetHandler::Create(
                    NotAllowedHandler::Create())
                );

        })))->Execute();

}
