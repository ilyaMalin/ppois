#pragma once

#include <string>
#include "common/forward.hpp"

class contactPerson
{
    std::string id;
    std::string name;
    std::string status;
    counterparty *counterpartyRef = nullptr;

public:
    contactPerson(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateContact() const;
    void confirmContact();
    void linkCounterparty(counterparty &);
};
