#ifndef REQUESTRULESOBJECT_H
#define REQUESTRULESOBJECT_H

#include "IRulesObject.h"
#include "UdpRequestData.h"
#include <memory>

using namespace std;

class RequestRulesObject;
using RequestRulesObjectPtr = shared_ptr<RequestRulesObject>;

class RequestRulesObject : public IRulesObject
{
    UdpRequestDataPtr m_object;
public:
    RequestRulesObject(UdpRequestDataPtr data);

    static RequestRulesObjectPtr Create(UdpRequestDataPtr data)
    {
        return make_shared<RequestRulesObject>(data);
    }

    IRulesPtr getRules() override;
    void setRules(IRulesPtr rules) override;
};

#endif // REQUESTRULESOBJECT_H
