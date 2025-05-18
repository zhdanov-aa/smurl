#ifndef SENDBADREQUESTCOMMAND_H
#define SENDBADREQUESTCOMMAND_H

#include "ICommand.h"
#include <boost/asio.hpp>
#include <memory>

class SendBadRequestCommand;
using SendBadRequestCommandPtr = std::shared_ptr<SendBadRequestCommand>;
using HttpSocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class SendBadRequestCommand : public ICommand
{
    HttpSocketPtr m_socket;

public:
    SendBadRequestCommand(HttpSocketPtr socket);

    static SendBadRequestCommandPtr Create(HttpSocketPtr socket)
    {
        return std::make_shared<SendBadRequestCommand>(socket);
    }

    void Execute() override;
};

#endif // SENDBADREQUESTCOMMAND_H
