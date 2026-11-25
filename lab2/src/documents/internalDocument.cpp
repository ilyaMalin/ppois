#include "documents/internalDocument.hpp"

#include <utility>

internalDocument::internalDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &internalDocument::getName() const
{
    return name;
}

const std::string &internalDocument::getStatus() const
{
    return status;
}

bool internalDocument::publishInternal() const
{
    return !id.empty() && !name.empty();
}

void internalDocument::withdrawInternal()
{
    status = "withdrawinternal";
}

void internalDocument::linkDepartment(department &value)
{
    departmentRef = &value;
}
