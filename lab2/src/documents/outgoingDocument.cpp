#include "documents/outgoingDocument.hpp"

#include <utility>

outgoingDocument::outgoingDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &outgoingDocument::getName() const
{
    return name;
}

const std::string &outgoingDocument::getStatus() const
{
    return status;
}

bool outgoingDocument::prepareDispatch() const
{
    return !id.empty() && !name.empty();
}

void outgoingDocument::markOutgoingSent()
{
    status = "markoutgoingsent";
}

void outgoingDocument::linkCounterparty(counterparty &value)
{
    counterpartyRef = &value;
}
