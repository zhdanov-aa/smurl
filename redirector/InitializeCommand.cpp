#include "InitializeCommand.h"
#include "IoC.h"
#include "UdpRequestData.h"

#include <memory>
#include <map>
#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

InitializeCommand::InitializeCommand()
{
}

void InitializeCommand::Execute()
{
    auto requests = make_shared<map<string, UdpRequestDataPtr>>();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Udp.Request.Register",
        RESOLVER([requests](UdpRequestDataPtr nr){
            std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
            (*requests)[requestId] = nr;
            return requestId;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Message.InterpretCommand.Get",
        RESOLVER([requests](std::string requestId)-> ICommandPtr {
            // std::vector<ICommandPtr> commands =
            //     {
            //         PrintJsonObjectCommand::Create(HttpRequestJsonObject::Create((*requests)[requestId])),
            //         RequestInterpretCommand::Create(requestId),
            //         DeleteHttpRequestCommand::Create(requests, requestId)
            //     };
            // return MacroCommand::Create(commands);
            return nullptr;
        }))->Execute();
}
