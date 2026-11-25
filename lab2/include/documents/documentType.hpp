#pragma once

#include <string>
#include "common/forward.hpp"

class documentType
{
    std::string id;
    std::string name;
    std::string status;
    workflowDefinition *workflowDefinitionRef = nullptr;

public:
    documentType(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateType() const;
    void enableType();
    void linkWorkflowDefinition(workflowDefinition &);
};
