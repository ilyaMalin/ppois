#include "documents/actDocument.hpp"

#include <utility>

actDocument::actDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &actDocument::getName() const
{
    return name;
}

const std::string &actDocument::getStatus() const
{
    return status;
}

bool actDocument::confirmAct() const
{
    return !id.empty() && !name.empty();
}

void actDocument::revokeAct()
{
    status = "revokeact";
}

void actDocument::linkCounterparty(counterparty &value)
{
    counterpartyRef = &value;
}
