#include "DeleteCommand.h"
#include "IoC.h"

DeleteCommand::DeleteCommand(std::string requestId)
    :m_requestId(requestId)
{
}


void DeleteCommand::Execute()
{
    IoC::Resolve<void>("Endpoint.Request.Delete", m_requestId)
}
