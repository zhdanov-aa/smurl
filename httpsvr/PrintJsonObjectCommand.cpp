#include "PrintJsonObjectCommand.h"

#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

PrintJsonObjectCommand::PrintJsonObjectCommand(IJsonObjectPtr jsonObject)
    : m_jsonObject(jsonObject)
{
}


void PrintJsonObjectCommand::Execute()
{
    auto json = m_jsonObject->getJson();

    // Сериализация в JSON
    std::stringstream ss;
    boost::property_tree::write_json(ss, *json);

    // Получаем JSON строку
    std::string json_result = ss.str();

    // Вывод результата
    std::cout << json_result << std::endl;
}
