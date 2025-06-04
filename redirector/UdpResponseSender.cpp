#include "UdpResponseSender.h"

UdpResponseSender::UdpResponseSender(UdpRequestDataPtr obj)
    :m_object(obj)
{
}

void UdpResponseSender::Send(string text)
{
    boost::asio::const_buffer buffer = boost::asio::buffer(text);
    m_object->m_pSocket->send_to(buffer, m_object->m_senderEndpoint);
}
