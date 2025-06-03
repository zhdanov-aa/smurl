#ifndef FINDREQUESTRULESCOMMAND_H
#define FINDREQUESTRULESCOMMAND_H

#include "ICommand.h"
#include "UdpRequestData.h"
#include "IJsonObject.h"
#include <memory>

using namespace std;

class FindRequestRulesCommand;
using FindRequestRulesCommandPtr = shared_ptr<FindRequestRulesCommand>;

class FindRequestRulesCommand : public ICommand
{
    UdpRequestDataPtr m_request;
    JsonPtr m_rules;

public:
    FindRequestRulesCommand(UdpRequestDataPtr request, JsonPtr rules);

    static FindRequestRulesCommandPtr Create(UdpRequestDataPtr request, JsonPtr rules)
    {
        return make_shared<FindRequestRulesCommand>(request, rules);
    }

    void Execute() override;
};

#endif // FINDREQUESTRULESCOMMAND_H
