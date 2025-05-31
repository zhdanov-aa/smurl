#ifndef DELETEREQUESTCOMMAND_H
#define DELETEREQUESTCOMMAND_H

#include "ICommand.h"
#include "UdpRequestData.h"
#include <memory>
#include <map>
#include <string>

using namespace std;

class DeleteRequestCommand;
using DeleteRequestCommandPtr = shared_ptr<DeleteRequestCommand>;

class DeleteRequestCommand : public ICommand
{
    shared_ptr<map<string, UdpRequestDataPtr>> m_requests;
    string m_requestId;

public:
    DeleteRequestCommand(shared_ptr<map<string, UdpRequestDataPtr>> requests, string requestId);

    static DeleteRequestCommandPtr Create(shared_ptr<map<string, UdpRequestDataPtr>> requests, string requestId)
    {
        return make_shared<DeleteRequestCommand>(requests, requestId);
    }

    void Execute() override;
};

#endif // DELETEREQUESTCOMMAND_H
