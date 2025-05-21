#include "CheckConditionCommand.h"
#include "RuntimeError.h"

CheckConditionCommand::CheckConditionCommand(IConditionPtr condition, JsonPtr json)
    :m_condition(condition), m_json(json)
{}


void CheckConditionCommand::Execute()
{
    if (!m_condition->Check(m_json))
    {
        throw new RuntimeError("CheckConditionCommand::Execute(): checking failed");
    }
}
