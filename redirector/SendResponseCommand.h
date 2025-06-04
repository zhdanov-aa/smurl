#ifndef SENDRESPONSECOMMAND_H
#define SENDRESPONSECOMMAND_H

#include "ICommand.h"
#include "IRulesObject.h"
#include "IResponseSender.h"
#include <memory>

using namespace std;

class SendResponseCommand;
using SendResponseCommandPtr = shared_ptr<SendResponseCommand>;

class SendResponseCommand : public ICommand
{
    IRulesObjectPtr m_rules;
    IResponseSenderPtr m_sender;

public:
    SendResponseCommand(IRulesObjectPtr rules, IResponseSenderPtr sender);

    static SendResponseCommandPtr Create(IRulesObjectPtr rules, IResponseSenderPtr sender)
    {
        return make_shared<SendResponseCommand>(rules, sender);
    }

    void Execute() override;
};

#endif // SENDRESPONSECOMMAND_H
