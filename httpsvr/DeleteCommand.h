#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "ICommand.h"
#include "IDeletingObject.h"
#include <memory>

class DeleteCommand;
using DeleteCommandPtr = std::shared_ptr<DeleteCommand>;

class DeleteCommand : public ICommand
{
    IDeletingObjectPtr m_object;

public:
    DeleteCommand(IDeletingObjectPtr obj);

    static DeleteCommandPtr Create(IDeletingObjectPtr obj)
    {
        return std::make_shared<DeleteCommand>(obj);
    }

    void Execute() override;
};

#endif // DELETECOMMAND_H
