#pragma once

#include <string>
#include "common/forward.hpp"

class contract
{
    std::string id;
    std::string name;
    std::string status;
    counterparty *counterpartyRef = nullptr;

public:
    contract(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateContract() const;
    void signContract();
    void linkCounterparty(counterparty &);
};
