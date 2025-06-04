#ifndef SENDNOTFOUNDCOMMAND_H
#define SENDNOTFOUNDCOMMAND_H

#include <ICommand.h>
#include <boost/asio.hpp>
#include <memory>

class SendNotFoundCommand;
using SendNotFoundCommandPtr = std::shared_ptr<SendNotFoundCommand>;
using HttpSocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class SendNotFoundCommand : public ICommand
{
    HttpSocketPtr m_socket;

public:
    SendNotFoundCommand(HttpSocketPtr socket);

    static SendNotFoundCommandPtr Create(HttpSocketPtr socket)
    {
        return std::make_shared<SendNotFoundCommand>(socket);
    }

    void Execute() override;
};

#endif // SENDNOTFOUNDCOMMAND_H
