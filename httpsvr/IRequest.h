#ifndef IREQUEST_H
#define IREQUEST_H

#include <memory>

class IRequest
{
public:
    virtual ~IRequest() = default;
    virtual void Accept() = 0;
};

using IRequestPtr = std::shared_ptr<IRequest>;

#endif // IREQUEST_H
