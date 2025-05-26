#ifndef IMESSAGEQUEUE_H
#define IMESSAGEQUEUE_H

#include <memory>
#include <string>

using namespace std;

class IMessageQueue;
using IMessageQueuePtr = shared_ptr<IMessageQueue>;

class IMessageQueue
{
public:
    virtual ~IMessageQueue() = default;
    virtual string GetMessage() = 0;
};

#endif // IMESSAGEQUEUE_H
