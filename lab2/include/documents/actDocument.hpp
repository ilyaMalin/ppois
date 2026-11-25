#pragma once

#include <string>
#include "common/forward.hpp"

class actDocument
{
    std::string id;
    std::string name;
    std::string status;
    counterparty *counterpartyRef = nullptr;

public:
    actDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool confirmAct() const;
    void revokeAct();
    void linkCounterparty(counterparty &);
};
