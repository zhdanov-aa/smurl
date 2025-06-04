#include "Endpoint.h"
#include "IoC.h"
#include <string>

Endpoint::Endpoint(IMessageQueuePtr mq, IOutputCommandStreamPtr cs)
    :m_mq(mq), m_cs(cs)
{
}

void Endpoint::EventLoop()
{
    while(true)
    {
        auto requestId = m_mq->GetMessage();

        m_cs->Write(IoC::Resolve<ICommandPtr>("Message.InterpretCommand.Get", requestId));
    }
}
