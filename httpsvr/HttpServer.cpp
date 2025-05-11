#include "HttpServer.h"
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>
#include <string>
#include <IoC.h>
#include "IHttpRequestHandler.h"
#include "IClient.h"
#include "HttpRequestInterpretCommand.h"
#include <IOutputCommandStream.h>

namespace http = boost::beast::http;

HttpServer::HttpServer()
{
}

void HttpServer::EventLoop()
{
    // Создаем контекст и сокет
     // boost::asio::io_context ioc;
     // boost::asio::ip::tcp::acceptor acceptor(ioc,
     //                                         boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));
    std::cout << "Сервер запущен на порту 8080" << std::endl;

    while(IoC::Resolve<bool>("Server.Alive.Get"))
    {
        auto client = IoC::Resolve<IHttpClientPtr>("Client.New");

        client->Accept();

        IoC::Resolve<IOutputCommandStreamPtr>("Server.OutputCommandStream.Get")->Write(
            IoC::Resolve<ICommandPtr>("Client.RequestInterpretCommand.New", client));

        // TODO: to command
        // if (!client.error())
        // {
        //     http::response<http::string_body> res;
        //     res = IoC::Resolve<IHttpRequestHandlerPtr>(
        //               "HttpSvr.RequestHandler.Get")->HandleRequest(client.request());

        //     http::write(client.socket(), res);
        // }
        // else
        // {
        //     // Формируем ответ об ошибке
        //     http::response<http::string_body> res;
        //     res.result(http::status::bad_request);
        //     res.set(http::field::content_type, "text/plain");
        //     res.body() = "Ошибка чтения запроса";
        //     res.content_length(res.body().size());
        //     res.keep_alive(true);

        //     // Отправляем ответ об ошибке
        //     http::write(client.socket(), res);
        // }

    }
}
