#ifndef IDELETINGOBJECT_H
#define IDELETINGOBJECT_H

#include <memory>

class IDeletingObject
{
public:
    virtual ~IDeletingObject() = default;

    virtual void Delete() = 0;
};

using IDeletingObjectPtr = std::shared_ptr<IDeletingObject>;

#endif // IDELETINGOBJECT_H
