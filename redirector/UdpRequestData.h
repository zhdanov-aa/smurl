#ifndef UDPREQUESTDATA_H
#define UDPREQUESTDATA_H

#include <memory>

using namespace std;

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
