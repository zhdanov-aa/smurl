#ifndef ENDPOINT_H
#define ENDPOINT_H

#include "IMessageQueue.h"
#include "IOutputCommandStream.h"

class Endpoint
{
    IMessageQueuePtr m_mq;
    IOutputCommandStreamPtr m_cs;

public:
    Endpoint(IMessageQueuePtr mq, IOutputCommandStreamPtr cs);

    void EventLoop();
};

#endif // ENDPOINT_H
