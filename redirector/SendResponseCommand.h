#ifndef SENDRESPONSECOMMAND_H
#define SENDRESPONSECOMMAND_H

#include "ICommand.h"
#include "UdpRequestData.h"
#include <memory>

using namespace std;

class SendResponseCommand;
using SendResponseCommandPtr = shared_ptr<SendResponseCommand>;

class SendResponseCommand : public ICommand
{
    UdpRequestDataPtr m_request;

public:
    SendResponseCommand(UdpRequestDataPtr request);

    static SendResponseCommandPtr Create(UdpRequestDataPtr request)
    {
        return make_shared<SendResponseCommand>(request);
    }

    void Execute() override;
};

#endif // SENDRESPONSECOMMAND_H
