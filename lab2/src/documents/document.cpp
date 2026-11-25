#include "documents/document.hpp"

#include <utility>

document::document(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &document::getName() const
{
    return name;
}

const std::string &document::getStatus() const
{
    return status;
}

bool document::prepareDocument() const
{
    return !id.empty() && !name.empty();
}

void document::submitDocument()
{
    status = "submit";
}

void document::linkEmployee(employee &value)
{
    employeeRef = &value;
}
