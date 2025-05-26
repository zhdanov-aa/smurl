#include "InitializeCommand.h"
#include "IoC.h"

InitializeCommand::InitializeCommand()
{
}

void InitializeCommand::Execute()
{
    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Alive.Get",
        RESOLVER([](){
            return true;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.New",
        RESOLVER([requests](){
            // static boost::asio::io_context ioc;
            // static std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor =
            //     std::make_shared<boost::asio::ip::tcp::acceptor>(
            //         ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8093));
            // std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
            // (*requests)[requestId] = std::make_shared<HttpRequest>(acceptor);
            // return requestId;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.AcceptingObject.Get",
        RESOLVER([requests](std::string requestId) -> IRequestAcceptingObjectPtr {
            // IRequestAcceptingObjectPtr acceptingObject = HttpRequestAcceptingObject::Create(
            //     (*requests)[requestId]);
            // return acceptingObject;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.OutputCommandStream.Get",
        RESOLVER([]() -> IOutputCommandStreamPtr {
            return DirectCommandExecutor::Create();
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.InterpretCommand.Get",
        RESOLVER([requests](std::string requestId)-> ICommandPtr {
            // std::vector<ICommandPtr> commands =
            //     {
            //         PrintJsonObjectCommand::Create(HttpRequestJsonObject::Create((*requests)[requestId])),
            //         RequestInterpretCommand::Create(requestId),
            //         DeleteHttpRequestCommand::Create(requests, requestId)
            //     };
            // return MacroCommand::Create(commands);
        }))->Execute();
}
