#include "documents/incomingDocument.hpp"

#include <utility>

incomingDocument::incomingDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &incomingDocument::getName() const
{
    return name;
}

const std::string &incomingDocument::getStatus() const
{
    return status;
}

bool incomingDocument::recordReceipt() const
{
    return !id.empty() && !name.empty();
}

void incomingDocument::markIncomingReviewed()
{
    status = "markincomingreviewed";
}

void incomingDocument::linkCounterparty(counterparty &value)
{
    counterpartyRef = &value;
}
