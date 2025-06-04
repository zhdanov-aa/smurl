#include "JsonFile.h"
#include <fstream>
#include <iostream>

using namespace std;

JsonFile::JsonFile(string fileName)
    :m_fileName(fileName)
{
}

JsonPtr JsonFile::getJson()
{
    if (m_json == nullptr)
    {
        ifstream file(m_fileName);
        if (!file.is_open())
        {
            cout << "Не удалось открыть файл " << m_fileName << endl;
        }

        // Читаем содержимое файла
        string json_str((istreambuf_iterator<char>(file)),
                             istreambuf_iterator<char>());

        m_json = make_shared<Json>(boost::json::parse(json_str));
    }

    return m_json;
}
