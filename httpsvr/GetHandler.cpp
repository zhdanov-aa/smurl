#include "GetHandler.h"
#include "SendRedirectCommand.h"
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
    // TODO: обратиться к микросервису для получения ссылки
    //IRedirectorPtr m_redirector;

    return SendRedirectCommand::Create(m_request->socketptr(), "https://mail.ru");
}
