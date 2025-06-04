#ifndef JSONFILE_H
#define JSONFILE_H

#include <IJsonObject.h>
#include <memory>
#include <string>

using namespace std;

class JsonFile;
using JsonFilePtr = shared_ptr<JsonFile>;

class JsonFile : public IJsonObject
{
    string m_fileName;
    JsonPtr m_json;

public:
    JsonFile(string fileName);

    static JsonFilePtr Create(string fileName)
    {
        return make_shared<JsonFile>(fileName);
    }

    JsonPtr getJson() override;
};

#endif // JSONFILE_H
