#include "organization/counterparty.hpp"

#include <utility>

counterparty::counterparty(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &counterparty::getName() const
{
    return name;
}

const std::string &counterparty::getStatus() const
{
    return status;
}

bool counterparty::validateCounterparty() const
{
    return !id.empty() && !name.empty();
}

void counterparty::approveCounterparty()
{
    status = "approvecounterparty";
}

void counterparty::linkAddress(address &value)
{
    addressRef = &value;
}
