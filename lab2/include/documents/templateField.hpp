#pragma once

#include <string>
#include "common/forward.hpp"

class templateField
{
    std::string id;
    std::string name;
    std::string status;
    documentTemplate *documentTemplateRef = nullptr;

public:
    templateField(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateTemplateField() const;
    void requireTemplateField();
    void linkDocumentTemplate(documentTemplate &);
};
