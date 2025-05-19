#ifndef IRULES_H
#define IRULES_H

#include "IJsonObject.h"
#include <memory>
#include <string>

using namespace std;

class IRules;
using IRulesPtr = shared_ptr<IRules>;

class IRules
{
public:
    virtual ~IRules() = default;
    virtual string Conclude(IJsonObjectPtr jsonObject) = 0;
};

#endif // IRULES_H
