#ifndef HTTPBADREQUESTCOMMAND_H
#define HTTPBADREQUESTCOMMAND_H

#include "ICommand.h"
#include <boost/asio.hpp>
#include <memory>

class HttpBadRequestCommand;
using HttpBadRequestCommandPtr = std::shared_ptr<HttpBadRequestCommand>;
using HttpSocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class HttpBadRequestCommand : public ICommand
{
    HttpSocketPtr m_socket;

public:
    HttpBadRequestCommand(HttpSocketPtr socket);

    static HttpBadRequestCommandPtr Create(HttpSocketPtr socket)
    {
        return std::make_shared<HttpBadRequestCommand>(socket);
    }

    void Execute() override;
};

#endif // HTTPBADREQUESTCOMMAND_H
