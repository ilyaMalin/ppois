#include "documents/documentType.hpp"

#include <utility>

documentType::documentType(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &documentType::getName() const
{
    return name;
}

const std::string &documentType::getStatus() const
{
    return status;
}

bool documentType::validateType() const
{
    return !id.empty() && !name.empty();
}

void documentType::enableType()
{
    status = "enabletype";
}

void documentType::linkWorkflowDefinition(workflowDefinition &value)
{
    workflowDefinitionRef = &value;
}
