#pragma once

#include <string>
#include "common/forward.hpp"

class documentVersion
{
    std::string id;
    std::string name;
    std::string status;
    document *documentRef = nullptr;

public:
    documentVersion(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool compareVersions() const;
    void restoreVersion();
    void linkDocument(document &);
};
