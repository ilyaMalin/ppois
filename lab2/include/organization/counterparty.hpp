#pragma once

#include <string>
#include "common/forward.hpp"

class counterparty
{
    std::string id;
    std::string name;
    std::string status;
    address *addressRef = nullptr;

public:
    counterparty(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateCounterparty() const;
    void approveCounterparty();
    void linkAddress(address &);
};
