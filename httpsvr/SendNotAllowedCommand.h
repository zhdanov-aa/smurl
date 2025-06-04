#ifndef SENDNOTALLOWEDCOMMAND_H
#define SENDNOTALLOWEDCOMMAND_H

#include "ICommand.h"
#include <boost/asio.hpp>
#include <memory>

class SendNotAllowedCommand;
using SendNotAllowedCommandPtr = std::shared_ptr<SendNotAllowedCommand>;
using HttpSocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class SendNotAllowedCommand : public ICommand
{
    HttpSocketPtr m_socket;

public:
    SendNotAllowedCommand(HttpSocketPtr socket);

    static SendNotAllowedCommandPtr Create(HttpSocketPtr socket)
    {
        return std::make_shared<SendNotAllowedCommand>(socket);
    }

    void Execute() override;
};

#endif // SENDNOTALLOWEDCOMMAND_H
