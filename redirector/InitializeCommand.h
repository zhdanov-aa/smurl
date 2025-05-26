#ifndef __INITIALIZECOMMAND_INCLUDED__
#define __INITIALIZECOMMAND_INCLUDED__

#include "ICommand.h"
#include <memory>

class InitializeCommand;
using InitializeCommandPtr = std::shared_ptr<InitializeCommand>;

class InitializeCommand: public ICommand
{
public:
    InitializeCommand();
    void Execute() override;
};

#endif