#ifndef BEFORECONDITION_H
#define BEFORECONDITION_H

#include "ICondition.h"
#include <memory>
#include <string>

class BeforeCondition;
using BeforeConditionPtr = std::shared_ptr<BeforeCondition>;

class BeforeCondition : public ICondition
{
    std::string m_parameter;

public:
    BeforeCondition(std::string parameter);

    static BeforeConditionPtr Create(std::string parameter)
    {
        return std::make_shared<BeforeCondition>(parameter);
    }

    bool Check(JsonPtr json) override;
};

#endif // BEFORECONDITION_H
