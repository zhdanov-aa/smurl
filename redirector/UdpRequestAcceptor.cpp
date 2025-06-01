#include "UdpRequestAcceptor.h"
#include "UdpRequestData.h"
#include "IoC.h"
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

    std::cout << "Адрес: " << request->m_senderEndpoint.address().to_string()
              << ", Порт: " << request->m_senderEndpoint.port() << std::endl ;

    boost::asio::const_buffer buffer = boost::asio::buffer(R"({"location":"http://github.com"})");

    // std::cout << "data: " << buffer.size() << std::endl;

    m_socket.send_to(buffer, request->m_senderEndpoint);

    return IoC::Resolve<string>("Udp.Request.Register", request);
}
