#include "documents/templateField.hpp"

#include <utility>

templateField::templateField(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &templateField::getName() const
{
    return name;
}

const std::string &templateField::getStatus() const
{
    return status;
}

bool templateField::validateTemplateField() const
{
    return !id.empty() && !name.empty();
}

void templateField::requireTemplateField()
{
    status = "requiretemplatefield";
}

void templateField::linkDocumentTemplate(documentTemplate &value)
{
    documentTemplateRef = &value;
}
