#ifndef DELETEHTTPREQUESTCOMMAND_H
#define DELETEHTTPREQUESTCOMMAND_H

#include "ICommand.h"
#include "HttpRequest.h"
#include <string>
#include <memory>
#include <map>

class DeleteHttpRequestCommand;
using DeleteHttpRequestCommandPtr = std::shared_ptr<DeleteHttpRequestCommand>;
using RequestMapPtr = std::shared_ptr<std::map<std::string, HttpRequestPtr>>;

class DeleteHttpRequestCommand : public ICommand
{
    RequestMapPtr m_requests;
    std::string m_requestId;

public:
    DeleteHttpRequestCommand(RequestMapPtr requests, std::string requestId);

    static DeleteHttpRequestCommandPtr Create(RequestMapPtr requests, std::string requestId)
    {
        return std::make_shared<DeleteHttpRequestCommand>(requests, requestId);
    }

    void Execute() override;
};

#endif // DELETEHTTPREQUESTCOMMAND_H
