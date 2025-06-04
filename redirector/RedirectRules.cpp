#include "RedirectRules.h"
#include "IException.h"
#include "RuntimeError.h"

RedirectRules::RedirectRules(string conclusion, ICommandPtr condition)
    :m_conclusion(conclusion), m_condition(condition)
{
}

RedirectRulesPtr RedirectRules::SetNext(RedirectRulesPtr next)
{
    m_next = next;
    return next;
}

string RedirectRules::Conclude()
{
    if (m_condition == nullptr)
    {
        return m_conclusion;
    }

    try
    {
        m_condition->Execute();
        return m_conclusion;
    }
    catch (IException *exception)
    {
        delete exception;
        if (m_next == nullptr)
            throw new RuntimeError("RedirectRules::Conclude(): m_next is nullptr");
        return m_next->Conclude();
    }
}
