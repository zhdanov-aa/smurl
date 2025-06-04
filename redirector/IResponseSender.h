#ifndef IRESPONSESENDER_H
#define IRESPONSESENDER_H

#include <memory>
#include <string>

using namespace std;

class IResponseSender
{
public:
    virtual ~IResponseSender() = default;
    virtual void Send(string text) = 0;
};

using IResponseSenderPtr = shared_ptr<IResponseSender>;

#endif // IRESPONSESENDER_H
