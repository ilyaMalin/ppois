#include "organization/contactPerson.hpp"

#include <utility>

contactPerson::contactPerson(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &contactPerson::getName() const
{
    return name;
}

const std::string &contactPerson::getStatus() const
{
    return status;
}

bool contactPerson::validateContact() const
{
    return !id.empty() && !name.empty();
}

void contactPerson::confirmContact()
{
    status = "confirmcontact";
}

void contactPerson::linkCounterparty(counterparty &value)
{
    counterpartyRef = &value;
}
