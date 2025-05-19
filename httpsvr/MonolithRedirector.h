#ifndef MONOLITHREDIRECTOR_H
#define MONOLITHREDIRECTOR_H

#include "IRedirector.h"
#include <memory>

class MonolithRedirector;
using MonolithRedirectorPtr = std::shared_ptr<MonolithRedirector>;

class MonolithRedirector : public IRedirector
{
public:
    MonolithRedirector();

    static MonolithRedirectorPtr Create()
    {
        return std::make_shared<MonolithRedirector>();
    }

    std::string Redirect(IJsonObjectPtr jsonObject) override;
};

#endif // MONOLITHREDIRECTOR_H
