#include "HttpServer.h"
#include <iostream>
#include <IException.h>
#include <IoC.h>
#include <ICommand.h>
#include "HttpGetHandler.h"
#include "HttpRequestTerminator.h"

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
    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Http.RequestHandler.Get",
        make_container(std::function<IHttpRequestHandlerPtr()>([](){
            return HttpGetHandler::Create(
                HttpRequestTerminator::Create()
                );
        })))->Execute();
}
