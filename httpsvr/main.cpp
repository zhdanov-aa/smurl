#include "HttpServer.h"
#include <iostream>
#include <IException.h>
#include <IoC.h>
#include <ICommand.h>
#include "HttpGetHandler.h"
#include "HttpRequestTerminator.h"
#include "IHttpClient.h"
#include "HttpClientInfo.h"
#include "HttpRequestInterpretCommand.h"
#include "IOutputCommandStream.h"
#include "DirectCommandExecutor.h"

void InitIoC();

int main()
{
    InitIoC();

    try
    {
        HttpServer svr;
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
    // std::shared_ptr<boost::asio::io_context> ioc = std::make_shared<boost::asio::io_context>();
    // std::shared_ptr<> endpoint = std::make_shared<>();
    // static std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor =
    //     std::make_shared<boost::asio::ip::tcp::acceptor>(
    //         boost::asio::io_context,
    //         boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Server.Alive.Get",
        make_container(std::function<bool()>([](){
            return true;
        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Client.New",
        make_container(std::function<IHttpClientPtr()>([](){
            static boost::asio::io_context ioc;
            static std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor =
                std::make_shared<boost::asio::ip::tcp::acceptor>(
                    ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8081));
            IHttpClientPtr client = std::make_shared<HttpClientInfo>(acceptor);
            return client;
        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Server.OutputCommandStream.Get",
        make_container(std::function<IOutputCommandStreamPtr()>([](){
            return DirectCommandExecutor::Create();
        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Client.RequestInterpretCommand.New",
        make_container(std::function<ICommandPtr(IHttpClientPtr)>([](IHttpClientPtr client){
            return HttpRequestInterpretCommand::Create(client);
        })))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "HttpRequestHandler.New",
        make_container(std::function<IHttpRequestHandlerPtr()>([](){
            return HttpGetHandler::Create(HttpRequestTerminator::Create());
        })))->Execute();

}
