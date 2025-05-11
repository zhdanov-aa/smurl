#ifndef HTTPREQUESTINTERPRETCOMMAND_H
#define HTTPREQUESTINTERPRETCOMMAND_H

#include <ICommand.h>
#include <memory>
#include "IRequest.h"

class HttpRequestInterpretCommand;
using HttpRequestInterpretCommandPtr = std::shared_ptr<HttpRequestInterpretCommand>;

class HttpRequestInterpretCommand : public ICommand
{
    IRequestPtr m_client;

public:
    HttpRequestInterpretCommand(IRequestPtr client);

    static HttpRequestInterpretCommandPtr Create(IRequestPtr client) { return std::make_shared<HttpRequestInterpretCommand>(client); }

    void Execute() override;
};

#endif // HTTPREQUESTINTERPRETCOMMAND_H
