#include "MonolithRedirector.h"
#include "IoC.h"
#include "IRules.h"

MonolithRedirector::MonolithRedirector(IJsonObjectPtr jsonObject)
    :m_jsonObject(jsonObject)
{
}

std::string MonolithRedirector::GetLocation()
{
    return IoC::Resolve<IRulesPtr>(
               "Redirector.Rules.Get",
               m_jsonObject
               )->Conclude();
}
