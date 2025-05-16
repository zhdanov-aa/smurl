#ifndef HTTPREDIRECTCOMMAND_H
#define HTTPREDIRECTCOMMAND_H

#include "ICommand.h"
#include <boost/asio.hpp>
#include <memory>
#include <string>

class HttpRedirectCommand;
using HttpRedirectCommandPtr = std::shared_ptr<HttpRedirectCommand>;
using HttpSocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class HttpRedirectCommand : public ICommand
{
    HttpSocketPtr m_socket;
    std::string m_location;

public:
    HttpRedirectCommand(HttpSocketPtr socket, std::string location);

    static HttpRedirectCommandPtr Create(HttpSocketPtr socket, std::string location)
    {
        return std::make_shared<HttpRedirectCommand>(socket, location);
    }

    void Execute() override;
};

#endif // HTTPREDIRECTCOMMAND_H
