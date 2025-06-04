#include "SendResponseCommand.h"
#include <sstream>

SendResponseCommand::SendResponseCommand(IRulesObjectPtr rules, IResponseSenderPtr sender)
    :m_rules(rules), m_sender(sender)
{
}

void SendResponseCommand::Execute()
{
    auto rules = m_rules->getRules();
    std::string location = "";

    if (rules != nullptr)
    {
        location = rules->Conclude();
    }

    boost::json::value response = {
        {"location", location }
    };

    std::stringstream response_stream;
    response_stream << response;
    std::string response_string = response_stream.str();

    m_sender->Send(response_string);
}
