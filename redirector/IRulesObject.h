#ifndef IRULESOBJECT_H
#define IRULESOBJECT_H

#include "IRules.h"
#include <memory>

class IRulesObject
{
public:
    virtual ~IRulesObject() = default;
    virtual IRulesPtr getRules() = 0;
    virtual void setRules(IRulesPtr rules) = 0;
};

using IRulesObjectPtr = shared_ptr<IRulesObject>;

#endif // IRULESOBJECT_H
