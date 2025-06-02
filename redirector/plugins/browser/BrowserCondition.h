#ifndef BROWSERCONDITION_H
#define BROWSERCONDITION_H

#include <ICondition.h>
#include <memory>
#include <string>

using namespace std;

class BrowserCondition;
using BrowserConditionPtr = shared_ptr<BrowserCondition>;

class BrowserCondition : public ICondition
{
    string m_parameter;

public:
    BrowserCondition(string parameter);

    static BrowserConditionPtr Create(string parameter)
    {
        return make_shared<BrowserCondition>(parameter);
    }

    bool Check(JsonPtr json) override;
};

#endif // BROWSERCONDITION_H
