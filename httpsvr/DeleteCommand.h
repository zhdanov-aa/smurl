#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "ICommand.h"
#include <string>
#include <memory>

class DeleteCommand;
using DeleteCommandPtr = std::shared_ptr<DeleteCommand>;

class DeleteCommand : public ICommand
{
    std::string m_requestId;

public:
    DeleteCommand(std::string requestId);

    static DeleteCommandPtr Create(std::string requestId)
    {
        return std::make_shared<DeleteCommand>(requestId);
    }

    void Execute() override;
};

#endif // DELETECOMMAND_H
