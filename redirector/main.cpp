#include "InitializeCommand.h"

int main()
{
    auto initCommand = InitializeCommand::Create();
    initCommand->Execute();
    
    // Установка обработчика в main()
    // signal(SIGINT, signalHandler);
    // signal(SIGTERM, signalHandler);

    // InitIoC();

    // try
    // {
    //     Endpoint svr;
    //     svr.EventLoop();
    // }
    // catch(std::exception& e)
    // {
    //     std::cerr << "Ошибка: " << e.what() << std::endl;
    //     return EXIT_FAILURE;
    // }
    // catch(IException *e)
    // {
    //     std::cerr << "Ошибка: " << e->WhatHappened() << std::endl;
    //     delete e;
    //     return EXIT_FAILURE;
    // }

    return EXIT_SUCCESS;
}