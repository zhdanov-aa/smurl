#ifndef PLUGINCONDITION_H
#define PLUGINCONDITION_H

#include "ICondition.h"
#include <memory>

using namespace std;

class PluginCondition;
using PluginConditionPtr = shared_ptr<PluginCondition>;

class PluginCondition : public ICondition
{
    string m_name;
    string m_parameter;

public:
    PluginCondition(string name, string parameter);

    static PluginConditionPtr Create(string name, string parameter)
    {
        return make_shared<PluginCondition>(name, parameter);
    }

    bool Check(JsonPtr json) override;
};

#endif // PLUGINCONDITION_H
