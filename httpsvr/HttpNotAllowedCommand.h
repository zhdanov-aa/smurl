#ifndef HTTPNOTALLOWEDCOMMAND_H
#define HTTPNOTALLOWEDCOMMAND_H

#include "ICommand.h"
#include <boost/asio.hpp>
#include <memory>

class HttpNotAllowedCommand;
using HttpNotAllowedCommandPtr = std::shared_ptr<HttpNotAllowedCommand>;
using HttpSocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class HttpNotAllowedCommand : public ICommand
{
    HttpSocketPtr m_socket;

public:
    HttpNotAllowedCommand(HttpSocketPtr socket);

    static HttpNotAllowedCommandPtr Create(HttpSocketPtr socket)
    {
        return std::make_shared<HttpNotAllowedCommand>(socket);
    }

    void Execute() override;
};

#endif // HTTPNOTALLOWEDCOMMAND_H
