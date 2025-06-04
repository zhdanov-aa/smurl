#include "RequestRulesObject.h"

RequestRulesObject::RequestRulesObject(UdpRequestDataPtr data)
    : m_object(data)
{
}

IRulesPtr RequestRulesObject::getRules()
{
    return m_object->rules;
}

void RequestRulesObject::setRules(IRulesPtr rules)
{
    m_object->rules = rules;
}
