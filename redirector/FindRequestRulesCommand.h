#ifndef FINDREQUESTRULESCOMMAND_H
#define FINDREQUESTRULESCOMMAND_H

#include "ICommand.h"
#include "UdpRequestData.h"
#include "IJsonObject.h"
#include "IRulesObject.h"
#include <memory>

using namespace std;

class FindRequestRulesCommand;
using FindRequestRulesCommandPtr = shared_ptr<FindRequestRulesCommand>;

class FindRequestRulesCommand : public ICommand
{
    IJsonObjectPtr m_request;
    JsonPtr m_rules;
    IRulesObjectPtr m_rulesObject;

public:
    FindRequestRulesCommand(IJsonObjectPtr request, JsonPtr rules, IRulesObjectPtr rulesObject);

    static FindRequestRulesCommandPtr Create(IJsonObjectPtr request, JsonPtr rules, IRulesObjectPtr rulesObject)
    {
        return make_shared<FindRequestRulesCommand>(request, rules, rulesObject);
    }

    void Execute() override;
};

#endif // FINDREQUESTRULESCOMMAND_H
