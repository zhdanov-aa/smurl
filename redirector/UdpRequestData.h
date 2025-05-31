#ifndef UDPREQUESTDATA_H
#define UDPREQUESTDATA_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>

using namespace std;
using boost::asio::ip::udp;

class UdpRequestData;
using UdpRequestDataPtr = shared_ptr<UdpRequestData>;

class UdpRequestData
{
public:
    UdpRequestData();

    static UdpRequestDataPtr Create()
    {
        return make_shared<UdpRequestData>();
    }
        
    boost::asio::mutable_buffer m_buffer;
    udp::endpoint m_senderEndpoint;
};

#endif // UDPREQUESTDATA_H
