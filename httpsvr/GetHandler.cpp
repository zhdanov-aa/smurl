#include "GetHandler.h"
#include "SendRedirectCommand.h"
#include "IRedirector.h"
#include "HttpRequestJsonObject.h"
#include "IoC.h"
#include "IException.h"
#include "SendNotFoundCommand.h"
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
    auto redirector = IoC::Resolve<IRedirectorPtr>(
        "Http.Redirector.Get",
        std::static_pointer_cast<IJsonObject>(HttpRequestJsonObject::Create(m_request)));

    try
    {
        auto newLoaction = redirector->GetLocation();
        if (newLoaction == "")
            return SendNotFoundCommand::Create(m_request->socketptr());
        else
            return SendRedirectCommand::Create(m_request->socketptr(), newLoaction);
    }
    catch(IException *exception)
    {
        delete exception;
        return SendNotFoundCommand::Create(m_request->socketptr());
    }
}
