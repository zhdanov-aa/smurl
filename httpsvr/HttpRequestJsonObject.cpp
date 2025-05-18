#include "HttpRequestJsonObject.h"

HttpRequestJsonObject::HttpRequestJsonObject(HttpRequestPtr request)
    : m_request(request)
{
}

JsonPtr HttpRequestJsonObject::getJson()
{
    JsonPtr root = std::make_shared<Json>();

    // Добавляем метод запроса
    root->put("method", m_request->request().method_string());

    // Добавляем URI
    root->put("uri", m_request->request().target());

    // Добавляем версию HTTP
    root->put("version", std::to_string(m_request->request().version()));

    // Сериализуем заголовки
    // Json headers;
    // for(auto& h : m_request->request()/*.base().headers()*/) {
    //     headers.put(
    //         std::to_string(h.name_string()),
    //         std::to_string(h.value())
    //         );
    // }
    // root->add_child("headers", headers);

    // Добавляем тело запроса
    root->put("body", m_request->request().body());

    return root;
}
