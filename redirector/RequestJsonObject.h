#ifndef REQUESTJSONOBJECT_H
#define REQUESTJSONOBJECT_H

#include "UdpRequestData.h"
#include <IJsonObject.h>
#include <memory>

using namespace std;

class RequestJsonObject;
using RequestJsonObjectPtr = shared_ptr<RequestJsonObject>;

class RequestJsonObject : public IJsonObject
{
    UdpRequestDataPtr m_requestData;

public:
    RequestJsonObject(UdpRequestDataPtr requestData);

    static RequestJsonObjectPtr Create(UdpRequestDataPtr requestData)
    {
        return make_shared<RequestJsonObject>(requestData);
    }

    JsonPtr getJson() override;
};

#endif // REQUESTJSONOBJECT_H
