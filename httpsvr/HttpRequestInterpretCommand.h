#ifndef HTTPREQUESTINTERPRETCOMMAND_H
#define HTTPREQUESTINTERPRETCOMMAND_H

#include <ICommand.h>
#include <memory>
#include "IClient.h"

class HttpRequestInterpretCommand;
using HttpRequestInterpretCommandPtr = std::shared_ptr<HttpRequestInterpretCommand>;

class HttpRequestInterpretCommand : public ICommand
{
    IHttpClientPtr m_client;

public:
    HttpRequestInterpretCommand(IHttpClientPtr client);

    static HttpRequestInterpretCommandPtr Create(IHttpClientPtr client) { return std::make_shared<HttpRequestInterpretCommand>(client); }

    void Execute() override;
};

#endif // HTTPREQUESTINTERPRETCOMMAND_H
