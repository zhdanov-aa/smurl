#include "FindRequestRulesCommand.h"
//#include "IoC.h"
#include "RequestJsonObject.h"
#include "RedirectRules.h"
#include "CheckConditionCommand.h"
#include "MacroCommand.h"

FindRequestRulesCommand::FindRequestRulesCommand(UdpRequestDataPtr request, JsonPtr rules)
    : m_request(request), m_rules(rules)
{
}


void FindRequestRulesCommand::Execute()
{
    auto request = RequestJsonObject::Create(m_request);

    // Цепочка правил
    RedirectRulesPtr firstRule = nullptr, lastRule = nullptr;

    // uri запроса
    auto json = request->getJson();
    auto target = json->at("target").as_string();

    // если есть праила для запроса
    if (m_rules->as_object().contains(target))
    {
        // Итерация по правилам
        for (const auto& ruleDesc : m_rules->as_object().at(target).as_object())
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

    m_request->rules = firstRule;
}
