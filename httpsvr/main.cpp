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

#include "IJsonObject.h"
#include "IRules.h"

#include "RuntimeError.h"

#include "HttpRequestAcceptor.h"
#include "HttpRequestJsonObject.h"

#include "MonolithRedirector.h"

#include "RedirectRules.h"
#include "CheckConditionCommand.h"
#include "BeforeCondition.h"

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

    Endpoint svr(
        HttpRequestAcceptor::Create(8080),
        DirectCommandExecutor::Create()
        );

    try
    {
        svr.EventLoop();
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
        "/search":
        {
            "http://mail.ru":
            {
                "before": "2025-05-24 13:20"
            },

            "http://google.ru":
            {
            }
        },
        "/mail":
        {
            "http://yandex.ru":
            {
            }
        }
    }
    )";

    JsonPtr jsonRules = std::make_shared<Json>(boost::json::parse(json_str));

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Http.Request.New",
        RESOLVER([requests](HttpRequestPtr nr){
            std::string requestId = boost::uuids::to_string(boost::uuids::random_generator()());
            (*requests)[requestId] = nr;
            return requestId;
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

            // Цепочка правил
            RedirectRulesPtr firstRule = nullptr, lastRule = nullptr;

            // uri запроса
            auto json = request->getJson();
            auto target = json->at("target").as_string();

            // если есть праила для запроса
            if (jsonRules->as_object().contains(target))
            {
                // Итерация по правилам
                for (const auto& ruleDesc : jsonRules->as_object().at(target).as_object())
                {
                    auto location = ruleDesc.key_c_str();

                    // Итаерация по командам
                    std::vector<ICommandPtr> commands;
                    for (const auto& conditionDesc : ruleDesc.value().as_object())
                    {
                        commands.push_back(
                            CheckConditionCommand::Create(
                                conditionDesc.key_c_str(),
                                conditionDesc.value().as_string().c_str(),
                                json
                                ));
                    }

                    auto newRule = RedirectRules::Create(location, MacroCommand::Create(commands));

                    if (firstRule == nullptr)
                    {
                        firstRule = lastRule = newRule;
                    }
                    else
                    {
                        lastRule = lastRule->SetNext(newRule);
                    }
                }
            }
            return firstRule;
        }))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Condition.Get",
        RESOLVER([](std::string condition, std::string parameter) -> IConditionPtr {
            // TODO: загрузка плагинов
            if (condition == "before")
            {
                return BeforeCondition::Create(parameter);
            }
            return nullptr;
        }))->Execute();
}
