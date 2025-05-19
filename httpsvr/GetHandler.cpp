#include "GetHandler.h"
#include "SendRedirectCommand.h"
#include "IRedirector.h"
#include "HttpRequestJsonObject.h"
#include "IoC.h"
#include <stdexcept>

namespace http = boost::beast::http;

GetHandler::GetHandler(HttpRequestPtr request)
    :m_request(request)
{}

bool GetHandler::CanHandle()
{
    return (m_request->request().method() == http::verb::get);
}

ICommandPtr GetHandler::Handle()
{
    auto redirector = IoC::Resolve<IRedirectorPtr>("Http.Redirector.Get");
    auto newLoaction = redirector->Redirect(HttpRequestJsonObject::Create(m_request));

    return SendRedirectCommand::Create(m_request->socketptr(), newLoaction);
}
