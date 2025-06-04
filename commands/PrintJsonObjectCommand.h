#ifndef PRINTJSONOBJECTCOMMAND_H
#define PRINTJSONOBJECTCOMMAND_H

#include "ICommand.h"
#include "IJsonObject.h"
#include <memory>

class PrintJsonObjectCommand;
using PrintJsonObjectCommandPtr = std::shared_ptr<PrintJsonObjectCommand>;

class PrintJsonObjectCommand : public ICommand
{
    IJsonObjectPtr m_jsonObject;

public:
    PrintJsonObjectCommand(IJsonObjectPtr jsonObject);

    static PrintJsonObjectCommandPtr Create(IJsonObjectPtr jsonObject)
    {
        return std::make_shared<PrintJsonObjectCommand>(jsonObject);
    }

    void Execute() override;
};

#endif // PRINTJSONOBJECTCOMMAND_H
