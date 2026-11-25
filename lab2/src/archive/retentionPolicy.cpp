#include "archive/retentionPolicy.hpp"

#include <utility>

retentionPolicy::retentionPolicy(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &retentionPolicy::getName() const
{
    return name;
}

const std::string &retentionPolicy::getStatus() const
{
    return status;
}

bool retentionPolicy::validateRetentionPolicy() const
{
    return !id.empty() && !name.empty();
}

void retentionPolicy::applyRetentionPolicy()
{
    status = "applyretentionpolicy";
}

void retentionPolicy::linkDocumentType(documentType &value)
{
    documentTypeRef = &value;
}
