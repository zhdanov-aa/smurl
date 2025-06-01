#include "UdpRequestAcceptor.h"
#include "UdpRequestData.h"
#include "IoC.h"

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

    return IoC::Resolve<string>("Udp.Request.Register", request);
}
