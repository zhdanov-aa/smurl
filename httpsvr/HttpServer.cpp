#include "HttpServer.h"
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>
#include <string>
#include <IoC.h>
#include "IHttpRequestHandler.h"

namespace http = boost::beast::http;

// // Обработчик входящих запросов с поддержкой HEAD
// http::response<http::string_body> handle_request(http::request<http::string_body>& req)
// {
//     http::response<http::string_body> res;

//     // Проверяем метод запроса
//     if (req.method() != http::verb::get)
//     {
//         res.result(http::status::method_not_allowed);
//         res.set(http::field::content_type, "text/plain");
//         res.body() = "Метод не поддерживается";
//         return res;
//     }

//     // Формируем ответ с перенаправлением
//     res.result(http::status::permanent_redirect);
//     res.set(http::field::location, "https://mail.ru");
//     res.set(http::field::content_type, "text/plain");
//     res.body() = "Вы будете перенаправлены на mail.ru";
//     res.content_length(res.body().size());
//     res.keep_alive(true);

//     return res;
// }

HttpServer::HttpServer()
{
}

void HttpServer::EventLoop()
{
    // Создаем контекст и сокет
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::acceptor acceptor(ioc,
                                            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));

    std::cout << "Сервер запущен на порту 8080" << std::endl;

    for(;;) {
        // Принимаем новое соединение
        boost::asio::ip::tcp::socket socket(ioc);
        acceptor.accept(socket);

        // Создаем буфер для запроса
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::response<http::string_body> res;

        // Читаем запрос с проверкой
        boost::beast::error_code ec;
        http::read(socket, buffer, req, ec);

        if (!ec)
        {
            res = IoC::Resolve<IHttpRequestHandlerPtr>(
                      "HttpSvr.RequestHandler.Get")->HandleRequest(req);

            http::write(socket, res);
        }
        else
        {
            // Формируем ответ об ошибке
            res.result(http::status::bad_request);
            res.set(http::field::content_type, "text/plain");
            res.body() = "Ошибка чтения запроса";
            res.content_length(res.body().size());
            res.keep_alive(true);

            // Отправляем ответ об ошибке
            http::write(socket, res, ec);
        }

        // Закрываем соединение
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        // Игнорируем ошибки при закрытии
        if(ec && ec != boost::beast::errc::not_connected)
            throw boost::beast::system_error{ec};
    }
}
