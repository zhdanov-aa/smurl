#include "BrowserCondition.h"
#include <algorithm>
#include <cctype>
#include <boost/json/src.hpp>
#include <iostream>

BrowserCondition::BrowserCondition(string parameter)
    :m_parameter(parameter)
{
}

bool BrowserCondition::Check(JsonPtr json)
{
    auto headers = json->at("headers").as_object();
    string user_agent_str = boost::json::value_to<std::string>(headers.at("User-Agent"));

    auto it = std::search(user_agent_str.begin(), user_agent_str.end(),
                          m_parameter.begin(), m_parameter.end(),
                          [](char a, char b) {
                              return std::tolower(a) == std::tolower(b);
                          });

    return it != user_agent_str.end();
}
