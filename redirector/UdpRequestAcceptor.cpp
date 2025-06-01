#include "UdpRequestAcceptor.h"
#include "UdpRequestData.h"
#include "IoC.h"
#include "IRules.h"
#include "RequestJsonObject.h"
#include "IJsonObject.h"
#include <iostream>

UdpRequestAcceptor::UdpRequestAcceptor(unsigned short port)
    :m_iocontext(), m_socket(m_iocontext), m_endpoint(udp::v4(), port)
{
    m_socket.open(m_endpoint.protocol());
    m_socket.bind(m_endpoint);
}


string UdpRequestAcceptor::GetMessage()
{
    auto request = UdpRequestData::Create();

    request->m_length = m_socket.receive_from(
        request->m_buffer, request->m_senderEndpoint);

// ------------

    std::string location = IoC::Resolve<IRulesPtr>(
                               "Redirector.Rules.Get",
                               std::static_pointer_cast<IJsonObject>(RequestJsonObject::Create(request))
                               )->Conclude();

    boost::json::value response = {
        {"location", location }
    };

    std::stringstream response_stream;
    response_stream << response;
    std::string response_string = response_stream.str();

    boost::asio::const_buffer buffer = boost::asio::buffer(response_string);

    m_socket.send_to(buffer, request->m_senderEndpoint);
// --------------
    return IoC::Resolve<string>("Udp.Request.Register", request);
}
