#ifndef HTTPREQUESTINTERPRETCOMMAND_H
#define HTTPREQUESTINTERPRETCOMMAND_H

#include "ICommand.h"
#include "HttpRequest.h"
#include <memory>

class HttpRequestInterpretCommand;
using HttpRequestInterpretCommandPtr = std::shared_ptr<HttpRequestInterpretCommand>;

class HttpRequestInterpretCommand : public ICommand
{
    HttpRequestPtr m_request;

public:
    HttpRequestInterpretCommand(HttpRequestPtr request);

    static HttpRequestInterpretCommandPtr Create(HttpRequestPtr request) { return std::make_shared<HttpRequestInterpretCommand>(request); }

    void Execute() override;
};

#endif // HTTPREQUESTINTERPRETCOMMAND_H
