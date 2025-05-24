#ifndef CONDITION_H
#define CONDITION_H

#include "ICondition.h"
#include <memory>
#include <string>

class Condition;
using ConditionPtr = std::shared_ptr<Condition>;

class Condition : public ICondition
{
    std::string m_condition;
    std::string m_value;

public:
    Condition(std::string condition, std::string value);

    static ConditionPtr Create(std::string condition, std::string value)
    {
        return std::make_shared<Condition>(condition, value);
    }

    bool Check(JsonPtr json) override;
};

#endif // CONDITION_H
