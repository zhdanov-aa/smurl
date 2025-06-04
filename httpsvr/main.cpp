#include "Endpoint.h"
#include "InitializeCommand.h"
#include "IException.h"
#include "IoC.h"
#include "HttpRequestAcceptor.h"
#include "DirectCommandExecutor.h"

#include <iostream>

int main()
{
    auto initCommand = InitializeCommand::Create();
    initCommand->Execute();

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
