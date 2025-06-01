#include "UdpRedirector.h"
#include "RuntimeError.h"

#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/json/string.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <chrono>
#include <thread>

using boost::asio::ip::udp;
using boost::json::value_from;
using boost::json::parse;

std::string value_to_string(const boost::json::value& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

class JsonUdpClient {
public:
    JsonUdpClient(boost::asio::io_service& io_service, const std::string& host, unsigned short port)
        : socket_(io_service, udp::endpoint(udp::v4(), 0)),
        remote_endpoint_(udp::endpoint(udp::v4(), port)),
        resolver_(io_service)
    {
        // Резолвим хост
        boost::asio::ip::udp::resolver::query query(host, std::to_string(port));
        remote_endpoint_ = *resolver_.resolve(query);
    }

    boost::json::value sendReceiveJson(const boost::json::value& json_data) {
        // Преобразуем JSON в строку
        std::string json_string = value_to_string(json_data);

        // Отправляем данные
        boost::asio::const_buffer buffer = boost::asio::buffer(json_string);
        socket_.send_to(buffer, remote_endpoint_);

        // Создаем буфер для ответа
        boost::array<char, 1024> recv_buffer;

        // Устанавливаем таймаут
        boost::asio::deadline_timer timer(socket_.get_executor());
        timer.expires_from_now(boost::posix_time::milliseconds(50));

        // Запускаем асинхронное чтение
        socket_.async_receive_from(
            boost::asio::buffer(recv_buffer),
            remote_endpoint_,
            boost::bind(&JsonUdpClient::handleReceive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));

        // Запускаем таймаут
        timer.async_wait(boost::bind(&JsonUdpClient::handleTimeout, this,
                                     boost::asio::placeholders::error));

        io_service_.run();

        // Если получили ответ
        if (response_received) {
            return parse(std::string(recv_buffer.data(), response_size));
        }

        return {};
    }

private:
    void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (!error) {
            response_received = true;
            response_size = bytes_transferred;
        }
        io_service_.stop();
    }

    void handleTimeout(const boost::system::error_code& error) {
        if (!error) {
            socket_.cancel();
            io_service_.stop();
        }
    }

    boost::asio::io_service io_service_;
    udp::socket socket_;
    udp::resolver resolver_;
    udp::endpoint remote_endpoint_;
    bool response_received = false;
    std::size_t response_size = 0;
};

UdpRedirector::UdpRedirector(IJsonObjectPtr jsonObject)
    :m_jsonObject(jsonObject)
{
}

std::string UdpRedirector::GetLocation()
{
    boost::asio::io_service io_service;
    JsonUdpClient client(io_service, "localhost", 8085);

    boost::json::value response = client.sendReceiveJson(*(m_jsonObject->getJson()));

    if (response.is_null())
    {
        throw new RuntimeError("UdpRedirector::GetLocation() failed");
    }
    else
    {
        return boost::json::value_to<std::string>(response.at("location"));
    }
}
