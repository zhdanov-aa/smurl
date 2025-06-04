#include "DeleteHttpRequestCommand.h"
#include "IoC.h"

DeleteHttpRequestCommand::DeleteHttpRequestCommand(RequestMapPtr requests, std::string requestId)
    :m_requests(requests), m_requestId(requestId)
{
}

void DeleteHttpRequestCommand::Execute()
{
    m_requests->erase(m_requestId);
}
