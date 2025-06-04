#include "FindRequestRulesCommand.h"
//#include "IoC.h"
#include "RequestJsonObject.h"
#include "RedirectRules.h"
#include "CheckConditionCommand.h"
#include "MacroCommand.h"

FindRequestRulesCommand::FindRequestRulesCommand(IJsonObjectPtr request, JsonPtr rules, IRulesObjectPtr rulesObject)
    : m_request(request), m_rules(rules), m_rulesObject(rulesObject)
{
}


void FindRequestRulesCommand::Execute()
{
    // Цепочка правил
    RedirectRulesPtr firstRule = nullptr, lastRule = nullptr;

    // uri запроса
    auto json = m_request->getJson();
    auto target = json->at("target").as_string();

    // если есть праила для запроса
    if (m_rules->as_object().contains(target))
    {
        // Итерация по правилам
        for (const auto& ruleDesc : m_rules->as_object().at(target).as_object())
        {
            auto new_location = ruleDesc.key_c_str();

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

            auto newRule = RedirectRules::Create(new_location, MacroCommand::Create(commands));

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

    m_rulesObject->setRules(firstRule);
}
