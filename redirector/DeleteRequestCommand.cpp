#include "DeleteRequestCommand.h"

DeleteRequestCommand::DeleteRequestCommand(shared_ptr<map<string, UdpRequestDataPtr> > requests, string requestId)
    :m_requests(requests), m_requestId(requestId)
{}


void DeleteRequestCommand::Execute()
{
    m_requests->erase(m_requestId);
}
