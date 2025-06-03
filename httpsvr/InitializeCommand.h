#ifndef INITIALIZECOMMAND_H
#define INITIALIZECOMMAND_H

#include <ICommand.h>
#include <memory>

using namespace std;

class InitializeCommand;
using InitializeCommandPtr = shared_ptr<InitializeCommand>;

class InitializeCommand : public ICommand
{
public:
    InitializeCommand();

    static InitializeCommandPtr Create()
    {
        return make_shared<InitializeCommand>();
    }

    void Execute() override;
};

#endif // INITIALIZECOMMAND_H
