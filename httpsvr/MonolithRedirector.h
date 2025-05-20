#ifndef MONOLITHREDIRECTOR_H
#define MONOLITHREDIRECTOR_H

#include "IRedirector.h"
#include "IJsonObject.h"
#include <memory>

class MonolithRedirector;
using MonolithRedirectorPtr = std::shared_ptr<MonolithRedirector>;

class MonolithRedirector : public IRedirector
{
    IJsonObjectPtr m_jsonObject;

public:
    MonolithRedirector(IJsonObjectPtr jsonObject);

    static MonolithRedirectorPtr Create(IJsonObjectPtr jsonObject)
    {
        return std::make_shared<MonolithRedirector>(jsonObject);
    }

    std::string GetLocation() override;
};

#endif // MONOLITHREDIRECTOR_H
