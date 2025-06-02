#include "PluginCondition.h"
// #include "RuntimeError.h"
#include <dlfcn.h>
#include <sstream>
#include <iostream>

PluginCondition::PluginCondition(string name, string parameter)
    :m_name(name), m_parameter(parameter)
{
}


bool PluginCondition::Check(JsonPtr json)
{
    typedef IConditionPtr (*ConditionBuilderFunction)(string);

    stringstream plugin_name;
    plugin_name << "./lib" << m_name << ".so";

    void *handle = dlopen(plugin_name.str().c_str(), RTLD_LAZY);

    if(handle == nullptr)
    {
        std::cout << "Error loading library: " << dlerror() << std::endl;
        return false;
    }

    auto conditionBuilder = reinterpret_cast<ConditionBuilderFunction>(dlsym(handle, "CreateCondition"));
    if(conditionBuilder == nullptr)
    {
        std::cout << "Error loading library: " << "getRule() not found" << std::endl;
        dlclose(handle);
        return false;
    }

    bool result = false;
    {
        IConditionPtr condition = conditionBuilder(m_parameter);
        if(condition != nullptr)
        {
            result = condition->Check(json);
        }
    }
    dlclose(handle);

    return result;
}
