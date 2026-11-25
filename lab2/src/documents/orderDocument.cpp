#include "documents/orderDocument.hpp"

#include <utility>

orderDocument::orderDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &orderDocument::getName() const
{
    return name;
}

const std::string &orderDocument::getStatus() const
{
    return status;
}

bool orderDocument::issueOrder() const
{
    return !id.empty() && !name.empty();
}

void orderDocument::cancelOrder()
{
    status = "cancelorder";
}

void orderDocument::linkEmployee(employee &value)
{
    employeeRef = &value;
}
