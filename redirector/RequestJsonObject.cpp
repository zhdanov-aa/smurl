#include "RequestJsonObject.h"
#include <boost/json/src.hpp>

RequestJsonObject::RequestJsonObject(UdpRequestDataPtr requestData)
    :m_requestData(requestData)
{
}

JsonPtr RequestJsonObject::getJson()
{
    // Получаем данные из буфера
    auto data = boost::asio::buffer_cast<const char*>(m_requestData->m_buffer);
    auto size = boost::asio::buffer_size(m_requestData->m_buffer);

    // Создаем строку
    std::string json_string(data, size);

    // Парсим JSON
    return make_shared<Json>(boost::json::parse(json_string));
}
