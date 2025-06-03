#include "UdpRequestData.h"

UdpRequestData::UdpRequestData()
    :m_buffer(m_data, sizeof(m_data)), m_pSocket(nullptr)
{
}
