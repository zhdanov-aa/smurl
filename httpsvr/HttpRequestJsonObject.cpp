#include "HttpRequestJsonObject.h"
#include <boost/json/src.hpp>


HttpRequestJsonObject::HttpRequestJsonObject(HttpRequestPtr request)
    : m_request(request)
{
}

JsonPtr HttpRequestJsonObject::getJson()
{
    auto req = m_request->request();
    boost::json::object obj = boost::json::object();

    // Добавляем основные поля
    obj.emplace("method", req.method_string());
    obj.emplace("target", req.target());
    obj.emplace("version", req.version());
    obj.emplace("body", req.body());

    // Сериализуем заголовки
    boost::json::object headers = boost::json::object();
    for (const auto& header : req) {
        //boost::json::object header_obj = boost::json::object();
        //header_obj.emplace("name", header.name_string());
        headers.emplace(header.name_string(), header.value());
        //header_obj.emplace("value", header.value());
        //headers.push_back(header_obj);
    }
    obj.emplace("headers", std::move(headers));

    return std::make_shared<Json>(obj);
}
