#include "InitializeCommand.h"
#include "IException.h"
#include "Endpoint.h"
#include "UdpRequestAcceptor.h"
#include "DirectCommandExecutor.h"
#include <iostream>

int main()
{
    auto initCommand = InitializeCommand::Create();
    initCommand->Execute();

    Endpoint svr(
        UdpRequestAcceptor::Create(8085),
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
