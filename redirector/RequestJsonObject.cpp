#include "RequestJsonObject.h"
#include <boost/json/src.hpp>

// #include <iostream>

RequestJsonObject::RequestJsonObject(UdpRequestDataPtr requestData)
    :m_requestData(requestData)
{
}

JsonPtr RequestJsonObject::getJson()
{
    // Получаем данные из буфера
    auto data = boost::asio::buffer_cast<const char*>(m_requestData->m_buffer);
    auto size = m_requestData->m_length;

    // Создаем строку
    std::string json_string(data, size);

    // std::cout << "string(" << size << "): " << json_string << std::endl;

    // Парсим JSON
    return make_shared<Json>(boost::json::parse(json_string));
}
