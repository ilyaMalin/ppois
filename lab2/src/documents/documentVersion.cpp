#include "documents/documentVersion.hpp"

#include <utility>

documentVersion::documentVersion(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &documentVersion::getName() const
{
    return name;
}

const std::string &documentVersion::getStatus() const
{
    return status;
}

bool documentVersion::compareVersions() const
{
    return !id.empty() && !name.empty();
}

void documentVersion::restoreVersion()
{
    status = "restoreversion";
}

void documentVersion::linkDocument(document &value)
{
    documentRef = &value;
}
