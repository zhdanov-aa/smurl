#ifndef CHECKCONDITIONCOMMAND_H
#define CHECKCONDITIONCOMMAND_H

#include "ICommand.h"
#include "ICondition.h"
#include <memory>

class CheckConditionCommand;
using CheckConditionCommandPtr = std::shared_ptr<CheckConditionCommand>;

class CheckConditionCommand : public ICommand
{
    IConditionPtr m_condition;
    JsonPtr m_json;

public:
    CheckConditionCommand(IConditionPtr condition, JsonPtr json);

    static CheckConditionCommandPtr Create(IConditionPtr condition, JsonPtr json)
    {
        return std::make_shared<CheckConditionCommand>(condition, json);
    }

    void Execute() override;
};

#endif // CHECKCONDITIONCOMMAND_H
