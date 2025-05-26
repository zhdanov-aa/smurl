#include "InitializeCommand.h"
#include "IoC.h"

InitializeCommand::InitializeCommand()
{
}

void InitializeCommand::Execute()
{
    // IoC::Resolve<ICommandPtr>(
    //     "IoC.Register",
    //     "Udp.Request.New",
    //     RESOLVER([requests](HttpRequestPtr nr){
    //         std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
    //         (*requests)[requestId] = nr;
    //         return requestId;
    //     }))->Execute();

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
