#include "documents/documentCategory.hpp"

#include <utility>

documentCategory::documentCategory(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &documentCategory::getName() const
{
    return name;
}

const std::string &documentCategory::getStatus() const
{
    return status;
}

bool documentCategory::classifyDocument() const
{
    return !id.empty() && !name.empty();
}

void documentCategory::activateCategory()
{
    status = "activatecategory";
}

void documentCategory::linkDocumentType(documentType &value)
{
    documentTypeRef = &value;
}
