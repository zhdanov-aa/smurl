#ifndef IHTTPREQUESTHANDLER_H
#define IHTTPREQUESTHANDLER_H

#include <boost/beast/http.hpp>
#include <memory>

namespace http = boost::beast::http;

class IHttpRequestHandler
{
public:
    virtual ~IHttpRequestHandler() = default;
    virtual http::response<http::string_body> HandleRequest(http::request<http::string_body>& req) = 0;
};

using IHttpRequestHandlerPtr = std::shared_ptr<IHttpRequestHandler>;

#endif // IHTTPREQUESTHANDLER_H
