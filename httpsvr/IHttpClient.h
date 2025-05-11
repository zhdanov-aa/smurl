#ifndef IHTTPCLIENT_H
#define IHTTPCLIENT_H

#include <memory>

class IHttpClient
{
public:
    virtual ~IHttpClient() = default;
    virtual void Accept() = 0;
};

using IHttpClientPtr = std::shared_ptr<IHttpClient>;

#endif // IHTTPCLIENT_H
