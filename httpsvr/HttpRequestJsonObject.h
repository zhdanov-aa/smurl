#ifndef HTTPREQUESTJSONOBJECT_H
#define HTTPREQUESTJSONOBJECT_H

#include "IJsonObject.h"
#include "HttpRequest.h"
#include <memory>

class HttpRequestJsonObject;
using HttpRequestJsonObjectPtr = std::shared_ptr<HttpRequestJsonObject>;

class HttpRequestJsonObject : public IJsonObject
{
    HttpRequestPtr m_request;

public:
    HttpRequestJsonObject(HttpRequestPtr request);

    static HttpRequestJsonObjectPtr Create(HttpRequestPtr request)
    {
        return std::make_shared<HttpRequestJsonObject>(request);
    }

    JsonPtr getJson() override;
};

#endif // HTTPREQUESTJSONOBJECT_H
