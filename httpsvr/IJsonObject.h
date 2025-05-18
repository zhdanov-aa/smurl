#ifndef IJSONOBJECT_H
#define IJSONOBJECT_H

#include <memory>
#include <boost/property_tree/ptree.hpp>

class IJsonObject;
using IJsonObjectPtr = std::shared_ptr<IJsonObject>;

using Json = boost::property_tree::ptree;
using JsonPtr = std::shared_ptr<Json>;

class IJsonObject
{
public:
    virtual ~IJsonObject() = default;

    virtual JsonPtr getJson() = 0;
};

#endif // IJSONOBJECT_H
