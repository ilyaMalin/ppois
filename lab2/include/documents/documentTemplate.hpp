#pragma once

#include <string>
#include "common/forward.hpp"

class documentTemplate
{
    std::string id;
    std::string name;
    std::string status;
    documentType *documentTypeRef = nullptr;

public:
    documentTemplate(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateTemplate() const;
    void publishTemplate();
    void linkDocumentType(documentType &);
};
