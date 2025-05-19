#include "MonolithRedirector.h"
#include "IoC.h"
#include "IRules.h"

MonolithRedirector::MonolithRedirector() {}


std::string MonolithRedirector::Redirect(IJsonObjectPtr jsonObject)
{
    // auto json = jsonObject->getJson();
    // auto rules = IoC::Resolver<IRulesPtr>("Redirector.Rules.Get", json->at("traget"));
    // return rules->Conclude(jsonObject);

    return "https://mail.ru";
}
