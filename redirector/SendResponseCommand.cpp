#include "SendResponseCommand.h"

SendResponseCommand::SendResponseCommand(UdpRequestDataPtr request)
    :m_request(request)
{
}

void SendResponseCommand::Execute()
{
    auto rules = m_request->rules;
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

    boost::asio::const_buffer buffer = boost::asio::buffer(response_string);

    m_request->m_pSocket->send_to(buffer, m_request->m_senderEndpoint);
}
