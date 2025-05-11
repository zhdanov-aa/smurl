#include "DirectCommandExecutor.h"

DirectCommandExecutor::DirectCommandExecutor() {}


void DirectCommandExecutor::Write(ICommandPtr command)
{
    command->Execute();
}
