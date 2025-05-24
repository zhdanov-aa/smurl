#include "Condition.h"
#include <string>
#include <ctime>
#include <cstring>
#include <cstdlib>

// #include <iostream>

bool isBeforeCurrentTime(const std::string& m_date) {
    // Проверяем корректность формата строки
    if (m_date.size() != 16 ||
        m_date[4] != '-' || m_date[7] != '-' ||
        m_date[10] != ' ' || m_date[13] != ':') {
        return false;
    }

    // Создаем tm структуру для входной даты
    std::tm input_tm = {};

    // Парсим год
    input_tm.tm_year = atoi(m_date.substr(0, 4).c_str()) - 1900;

    // Парсим месяц
    input_tm.tm_mon = atoi(m_date.substr(5, 2).c_str()) - 1;

    // Парсим день
    input_tm.tm_mday = atoi(m_date.substr(8, 2).c_str());

    // Парсим час
    input_tm.tm_hour = atoi(m_date.substr(11, 2).c_str());

    // Парсим минуты
    input_tm.tm_min = atoi(m_date.substr(14, 2).c_str());

    // Устанавливаем секунды в 0
    input_tm.tm_sec = 0;

    // Получаем текущее время
    time_t now = time(0);
    std::tm now_tm = *localtime(&now);

    // Преобразуем tm структуры в time_t
    time_t input_time = mktime(&input_tm);
    time_t current_time = mktime(&now_tm);

    // Сравниваем времена
    return input_time > current_time;
}

Condition::Condition(std::string condition, std::string value)
    :m_condition(condition), m_value(value)
{
}

bool Condition::Check(JsonPtr json)
{
    if (m_condition == "before")
    {
        auto result = isBeforeCurrentTime(m_value);
        return result;
    }

    return false;
}
