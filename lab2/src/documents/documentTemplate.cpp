#include "documents/documentTemplate.hpp"

#include <utility>

documentTemplate::documentTemplate(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &documentTemplate::getName() const
{
    return name;
}

const std::string &documentTemplate::getStatus() const
{
    return status;
}

bool documentTemplate::validateTemplate() const
{
    return !id.empty() && !name.empty();
}

void documentTemplate::publishTemplate()
{
    status = "publishtemplate";
}

void documentTemplate::linkDocumentType(documentType &value)
{
    documentTypeRef = &value;
}
