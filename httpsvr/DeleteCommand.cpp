#include "DeleteCommand.h"
#include "InvalidArgument.h"

DeleteCommand::DeleteCommand(IDeletingObjectPtr obj)
    :m_object(obj)
{
}


void DeleteCommand::Execute()
{
    if (m_object == nullptr)
        throw new InvalidArgument("DeleteCommand::Execute(): object is nullptr");

    m_object->Delete();
}
