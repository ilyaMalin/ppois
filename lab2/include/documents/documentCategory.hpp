#pragma once

#include <string>
#include "common/forward.hpp"

class documentCategory
{
    std::string id;
    std::string name;
    std::string status;
    documentType *documentTypeRef = nullptr;

public:
    documentCategory(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool classifyDocument() const;
    void activateCategory();
    void linkDocumentType(documentType &);
};
