#include "InitializeCommand.h"
#include "IException.h"
#include "Endpoint.h"
#include <iostream>

int main()
{
    auto initCommand = InitializeCommand::Create();
    initCommand->Execute();

    try
    {
        Endpoint svr;
        svr.EventLoop();
    }
    catch(IException *e)
    {
        std::cerr << "Исключение IException: " << e->WhatHappened() << std::endl;
        delete e;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
