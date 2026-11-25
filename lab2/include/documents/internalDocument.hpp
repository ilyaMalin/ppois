#pragma once

#include <string>
#include "common/forward.hpp"

class internalDocument
{
    std::string id;
    std::string name;
    std::string status;
    department *departmentRef = nullptr;

public:
    internalDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool publishInternal() const;
    void withdrawInternal();
    void linkDepartment(department &);
};
