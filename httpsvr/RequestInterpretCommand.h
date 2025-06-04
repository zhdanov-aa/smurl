#ifndef REQUESTINTERPRETCOMMAND_H
#define REQUESTINTERPRETCOMMAND_H

#include "ICommand.h"
#include <string>
#include <memory>

class RequestInterpretCommand;
using RequestInterpretCommandPtr = std::shared_ptr<RequestInterpretCommand>;

class RequestInterpretCommand : public ICommand
{
    std::string m_requestId;

public:
    RequestInterpretCommand(std::string requestId);

    static RequestInterpretCommandPtr Create(std::string requestId)
    {
        return std::make_shared<RequestInterpretCommand>(requestId);
    }

    void Execute() override;
};

#endif // REQUESTINTERPRETCOMMAND_H
