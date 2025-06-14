#include "InitializeCommand.h"
#include "MacroCommand.h"
#include "IoC.h"
#include "UdpRequestData.h"
#include "DeleteRequestCommand.h"
#include "UdpRequestAcceptor.h"
#include "DirectCommandExecutor.h"
#include "RequestJsonObject.h"
#include "PluginCondition.h"
#include "FindRequestRulesCommand.h"
#include "SendResponseCommand.h"
#include "RequestRulesObject.h"
#include "UdpResponseSender.h"
#include "JsonFile.h"

#include <memory>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

InitializeCommand::InitializeCommand()
{
}

void InitializeCommand::Execute()
{
    auto requests = make_shared<map<string, UdpRequestDataPtr>>();
    IJsonObjectPtr rulesDescription = JsonFile::Create("./rules.json");

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Rules.Description.Get",
        RESOLVER([rulesDescription]()-> IJsonObjectPtr {
            return rulesDescription;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Message.Queue.Get",
        RESOLVER([]()-> IMessageQueuePtr {
            return UdpRequestAcceptor::Create(8085);
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Message.Handler.CommandStream.Get",
        RESOLVER([]()-> IOutputCommandStreamPtr {
            return DirectCommandExecutor::Create();
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Message.InterpretCommand.Get",
        RESOLVER([requests](std::string requestId)-> ICommandPtr {
            auto requestData = (*requests)[requestId];
            auto requestRules = RequestRulesObject::Create(requestData);
            auto responseSender = UdpResponseSender::Create(requestData);
            std::vector<ICommandPtr> commands =
                {
                    FindRequestRulesCommand::Create(
                        RequestJsonObject::Create(requestData),
                        IoC::Resolve<IJsonObjectPtr>("Rules.Description.Get"),
                        requestRules),
                    SendResponseCommand::Create(requestRules, responseSender),
                    DeleteRequestCommand::Create(requests, requestId)
                };
            return MacroCommand::Create(commands);
        }))->Execute();

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
        "Condition.Get",
        RESOLVER([](std::string condition, std::string parameter) -> IConditionPtr {
            return PluginCondition::Create(condition, parameter);
        }))->Execute();
}
