#ifndef UDPREQUESTDATA_H
#define UDPREQUESTDATA_H

#include "IRules.h"

#include <memory>
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>

using namespace std;
using boost::asio::ip::udp;

class UdpRequestData;
using UdpRequestDataPtr = shared_ptr<UdpRequestData>;

class UdpRequestData
{
    char m_data[1024];

public:
    UdpRequestData();

    static UdpRequestDataPtr Create()
    {
        return make_shared<UdpRequestData>();
    }

    udp::socket *m_pSocket;
    boost::asio::mutable_buffer m_buffer;
    size_t m_length;
    udp::endpoint m_senderEndpoint;

    IRulesPtr rules;
};

#endif // UDPREQUESTDATA_H
