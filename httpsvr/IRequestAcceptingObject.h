#ifndef IREQUESTACCEPTINGOBJECT_H
#define IREQUESTACCEPTINGOBJECT_H

#include <memory>

class IRequestAcceptingObject
{
public:
    virtual ~IRequestAcceptingObject() = default;

    virtual void Accept() = 0;
};

using IRequestAcceptingObjectPtr = std::shared_ptr<IRequestAcceptingObject>;

#endif // IREQUESTACCEPTINGOBJECT_H
