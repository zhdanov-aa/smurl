#ifndef DIRECTCOMMANDEXECUTOR_H
#define DIRECTCOMMANDEXECUTOR_H

#include <IOutputCommandStream.h>
#include <memory>

class DirectCommandExecutor;
using DirectCommandExecutorPtr = std::shared_ptr<DirectCommandExecutor>;

class DirectCommandExecutor : public IOutputCommandStream
{
public:
    DirectCommandExecutor();

    static DirectCommandExecutorPtr Create() { return std::make_shared<DirectCommandExecutor>(); }

    void Write(ICommandPtr command) override;
};

#endif // DIRECTCOMMANDEXECUTOR_H
