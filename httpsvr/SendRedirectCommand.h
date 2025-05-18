#ifndef SENDREDIRECTCOMMAND_H
#define SENDREDIRECTCOMMAND_H

#include "ICommand.h"
#include <boost/asio.hpp>
#include <memory>
#include <string>

class SendRedirectCommand;
using SendRedirectCommandPtr = std::shared_ptr<SendRedirectCommand>;
using HttpSocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class SendRedirectCommand : public ICommand
{
    HttpSocketPtr m_socket;
    std::string m_location;

public:
    SendRedirectCommand(HttpSocketPtr socket, std::string location);

    static SendRedirectCommandPtr Create(HttpSocketPtr socket, std::string location)
    {
        return std::make_shared<SendRedirectCommand>(socket, location);
    }

    void Execute() override;
};

#endif // SENDREDIRECTCOMMAND_H
