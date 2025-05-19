#include "PrintJsonObjectCommand.h"
#include <iostream>

PrintJsonObjectCommand::PrintJsonObjectCommand(IJsonObjectPtr jsonObject)
    : m_jsonObject(jsonObject)
{
}

void PrintJsonObjectCommand::Execute()
{
    auto json = m_jsonObject->getJson();
    std::cout << boost::json::serialize(*json) << std::endl;
}
