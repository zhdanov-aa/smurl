#ifndef IOUTPUTCOMMANDSTREAM_H
#define IOUTPUTCOMMANDSTREAM_H

#include <ICommand.h>
#include <memory>

class IOutputCommandStream
{
public:
    virtual ~IOutputCommandStream() = default;

    virtual void Write(ICommandPtr command) = 0;
};

using IOutputCommandStreamPtr = std::shared_ptr<IOutputCommandStream>;

#endif // IOUTPUTCOMMANDSTREAM_H
