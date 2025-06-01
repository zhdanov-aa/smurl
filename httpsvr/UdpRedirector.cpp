#include "UdpRedirector.h"
#include "RuntimeError.h"

#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <chrono>
#include <thread>

using boost::asio::ip::udp;
using boost::json::value_from;
using boost::json::parse;

// std::string value_to_string(const boost::json::value& value) {
//     std::stringstream ss;
//     ss << value;
//     return ss.str();
// }

bool sendReceiveUdp(const std::string& message,
                    const std::string& host,
                    unsigned short port,
                    std::string& response,
                    int timeout_ms = 50) {
    try {
        boost::asio::io_service io_service;
        udp::socket socket(io_service);
        udp::resolver resolver(io_service);
        udp::resolver::query query(udp::v4(), host, std::to_string(port));
        udp::endpoint receiver_endpoint = *resolver.resolve(query);

        // Открываем сокет
        socket.open(udp::v4());

        // Отправляем сообщение
        boost::asio::const_buffer buffer = boost::asio::buffer(message);
        socket.send_to(buffer, receiver_endpoint);

        // Устанавливаем таймаут
        boost::asio::deadline_timer timer(io_service);
        timer.expires_from_now(boost::posix_time::milliseconds(timeout_ms));

        // Создаем буфер для ответа
        boost::array<char, 1024> recv_buffer;
        udp::endpoint sender_endpoint;

        // Ждем ответа с таймаутом
        boost::system::error_code error;
        size_t bytes_received = 0;

        timer.async_wait(
            [&](const boost::system::error_code& ec) {
                if (!ec) {
                    socket.cancel();
                }
            }
            );

        try {
            bytes_received = socket.receive_from(
                boost::asio::buffer(recv_buffer),
                sender_endpoint,
                0,
                error
                );
        } catch (...) {
            // Игнорируем исключения
        }

        // Проверяем, получили ли ответ
        if (!error) {
            response = std::string(recv_buffer.data(), bytes_received);
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return false;
}

UdpRedirector::UdpRedirector(IJsonObjectPtr jsonObject)
    :m_jsonObject(jsonObject)
{
}

std::string UdpRedirector::GetLocation()
{
    std::string response;
    std::string message = R"({ "key":"value" })";

    if (sendReceiveUdp(message, "localhost", 8085, response)) {
        std::cout << "Получен ответ: " << response << std::endl;
    } else {
        std::cout << "Таймаут или ошибка при получении ответа" << std::endl;
    }

    throw new RuntimeError("UdpRedirector::GetLocation() failed");
}
