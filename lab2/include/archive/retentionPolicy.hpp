#pragma once

#include <string>
#include "common/forward.hpp"

class retentionPolicy
{
    std::string id;
    std::string name;
    std::string status;
    documentType *documentTypeRef = nullptr;

public:
    retentionPolicy(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateRetentionPolicy() const;
    void applyRetentionPolicy();
    void linkDocumentType(documentType &);
};
