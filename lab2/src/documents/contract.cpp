#include "documents/contract.hpp"

#include <utility>

contract::contract(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &contract::getName() const
{
    return name;
}

const std::string &contract::getStatus() const
{
    return status;
}

bool contract::validateContract() const
{
    return !id.empty() && !name.empty();
}

void contract::signContract()
{
    status = "signcontract";
}

void contract::linkCounterparty(counterparty &value)
{
    counterpartyRef = &value;
}
