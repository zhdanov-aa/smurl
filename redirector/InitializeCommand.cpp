#include "InitializeCommand.h"
#include "MacroCommand.h"
#include "IoC.h"
#include "UdpRequestData.h"
#include "DeleteRequestCommand.h"
#include "IMessageQueue.h"
#include "UdpRequestAcceptor.h"
#include "IOutputCommandStream.h"
#include "DirectCommandExecutor.h"
#include "PrintJsonObjectCommand.h"
#include "RequestJsonObject.h"
#include "IRules.h"
#include "RedirectRules.h"
#include "CheckConditionCommand.h"
#include "ICondition.h"
#include "BeforeCondition.h"

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

    std::string json_str = R"(
    {
        "/search":
        {
            "http://mail.ru":
            {
                "before": "2025-06-02 13:20"
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
            std::vector<ICommandPtr> commands =
                {
                    PrintJsonObjectCommand::Create(RequestJsonObject::Create((*requests)[requestId])),
                    // RequestInterpretCommand::Create(requestId),
                    DeleteRequestCommand::Create(requests, requestId)
                };
            return MacroCommand::Create(commands);
            return nullptr;
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
