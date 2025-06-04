#include "DirectCommandExecutor.h"

DirectCommandExecutor::DirectCommandExecutor() {}


void DirectCommandExecutor::Write(ICommandPtr command)
{
    if (command != nullptr)
    {
        command->Execute();
    }
}
