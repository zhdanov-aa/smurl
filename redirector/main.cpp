#include "Endpoint.h"
#include "InitializeCommand.h"
#include "IException.h"
#include "IMessageQueue.h"
#include "IOutputCommandStream.h"
#include "IoC.h"
#include <iostream>

int main()
{
    auto initCommand = InitializeCommand::Create();
    initCommand->Execute();

    Endpoint svr(
        IoC::Resolve<IMessageQueuePtr>("Message.Queue.Get"),
        IoC::Resolve<IOutputCommandStreamPtr>("Message.Handler.CommandStream.Get")
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
