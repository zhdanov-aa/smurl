#ifndef REDIRECTRULES_H
#define REDIRECTRULES_H

#include "IRules.h"
#include "ICommand.h"
#include <memory>
#include <string>

using namespace std;

class RedirectRules;
using RedirectRulesPtr = shared_ptr<RedirectRules>;

class RedirectRules : public IRules
{
    string m_conclusion;
    ICommandPtr m_condition;
    RedirectRulesPtr m_next;

public:
    RedirectRules(string conclusion, ICommandPtr condition);

    static RedirectRulesPtr Create(string conclusion, ICommandPtr condition)
    {
        return make_shared<RedirectRules>(conclusion, condition);
    }

    RedirectRulesPtr SetNext(RedirectRulesPtr next);

    string Conclude() override;
};

#endif // REDIRECTRULES_H
