#include "Endpoint.h"
#include <IException.h>
#include <IoC.h>
#include <ICommand.h>
#include "GetHandler.h"
#include "NotAllowedHandler.h"
#include "BadRequestHandler.h"
#include "HttpRequest.h"

#include "RequestInterpretCommand.h"
#include "DeleteHttpRequestCommand.h"
#include "MacroCommand.h"
#include "PrintJsonObjectCommand.h"

#include "IOutputCommandStream.h"
#include "DirectCommandExecutor.h"

#include "IRequestAcceptingObject.h"
#include "IJsonObject.h"
#include "IRules.h"

#include "RuntimeError.h"

#include "HttpRequestAcceptingObject.h"
#include "HttpRequestJsonObject.h"

#include "MonolithRedirector.h"

#include "RedirectRules.h"
#include "CheckConditionCommand.h"
#include "Condition.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <map>
#include <string>
#include <vector>
#include <iostream>

void InitIoC();

int main()
{
    InitIoC();

    try
    {
        Endpoint svr;
        svr.EventLoop();
    }
    catch(std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch(IException *e)
    {
        std::cerr << "Ошибка: " << e->WhatHappened() << std::endl;
        delete e;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void InitIoC()
{
    auto requests = std::make_shared<std::map<std::string, HttpRequestPtr>>();

    std::string json_str = R"(
    {
        "/search": [
            {
                "location": "http://mail.ru",
                "conditions": {
                    "before": "2025-05-25 11:20"
                }

            },
            {
                "location": "http://google.ru",
                "conditions": {
                }
            }
        ]
    }
    )";

    JsonPtr jsonRules = std::make_shared<Json>(boost::json::parse(json_str));

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
            static boost::asio::io_context ioc;
            static std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor =
                std::make_shared<boost::asio::ip::tcp::acceptor>(
                    ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8088));
            std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
            (*requests)[requestId] = std::make_shared<HttpRequest>(acceptor);
            return requestId;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.AcceptingObject.Get",
        RESOLVER([requests](std::string requestId) -> IRequestAcceptingObjectPtr {
            IRequestAcceptingObjectPtr acceptingObject = HttpRequestAcceptingObject::Create(
                (*requests)[requestId]);
            return acceptingObject;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.JsonObject.Get",
        RESOLVER([requests](std::string requestId){
            IJsonObjectPtr jsonObject = HttpRequestJsonObject::Create(
                (*requests)[requestId]);
            return jsonObject;
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
            std::vector<ICommandPtr> commands =
                {
                    PrintJsonObjectCommand::Create(HttpRequestJsonObject::Create((*requests)[requestId])),
                    RequestInterpretCommand::Create(requestId),
                    DeleteHttpRequestCommand::Create(requests, requestId)
                };
            return MacroCommand::Create(commands);
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Endpoint.Request.Handler.Get",
        RESOLVER([requests](std::string requestId) -> IRequestHandlerPtr {
            RequestHandlerPtr handler = BadRequestHandler::Create((*requests)[requestId]);
            handler->SetNext(GetHandler::Create((*requests)[requestId]))
                ->SetNext(NotAllowedHandler::Create((*requests)[requestId]));
            return handler;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Http.Redirector.Get",
        RESOLVER([](IJsonObjectPtr jsonObject) -> IRedirectorPtr {
            return MonolithRedirector::Create(jsonObject);
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Redirector.Rules.Get",
        RESOLVER([jsonRules](IJsonObjectPtr request) -> IRulesPtr {
            RedirectRulesPtr first = nullptr, last = nullptr;
            auto json = request->getJson();
            auto target = json->at("target").as_string();
            boost::json::value v;
            if (jsonRules->as_object().contains(target))
            {
                auto rules = jsonRules->as_object().at(target).as_array();
                for (auto it = rules.begin(); it != rules.end(); ++it)
                {
                    auto location = it->at("location").as_string().c_str();

                    auto conditions = it->at("conditions").as_object();
                    std::vector<ICommandPtr> commands;
                    for (const auto& keyValue : conditions)
                    {
                        commands.push_back(
                            CheckConditionCommand::Create(
                                // Condition::Create(key.as_string().c_str(), value.as_string().c_str()),
                                Condition::Create(keyValue.key_c_str(), keyValue.value().as_string().c_str()),
                                json
                                ));
                    }

                    // ICommandPtr macroCommand;
                    // if (!commands.empty())
                    // {
                    //     macroCommand = MacroCommand::Create(commands);
                    // }

                    auto newRule = RedirectRules::Create(location, MacroCommand::Create(commands));

                    if (first == nullptr)
                    {
                        first = last = newRule;
                    }
                    else
                    {
                        last = last->SetNext(newRule);
                    }
                }
            }
            return first;
        }))->Execute();
}
