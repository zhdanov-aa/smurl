#ifndef HTTPREQUESTACCEPTINGOBJECT_H
#define HTTPREQUESTACCEPTINGOBJECT_H

#include "IRequestAcceptingObject.h"
#include "HttpRequest.h"
#include <memory>

class HttpRequestAcceptingObject;
using HttpRequestAcceptingObjectPtr = std::shared_ptr<HttpRequestAcceptingObject>;

class HttpRequestAcceptingObject : public IRequestAcceptingObject
{
    HttpRequestPtr m_request;

public:
    HttpRequestAcceptingObject(HttpRequestPtr request);

    static HttpRequestAcceptingObjectPtr Create(HttpRequestPtr request)
    {
        return std::make_shared<HttpRequestAcceptingObject>(request);
    }

    void Accept() override;
};

#endif // HTTPREQUESTACCEPTINGOBJECT_H
