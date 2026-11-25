#pragma once

#include <string>
#include "common/forward.hpp"

class position
{
    std::string id;
    std::string name;
    std::string status;
    department *departmentRef = nullptr;

public:
    position(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validatePosition() const;
    void activatePosition();
    void linkDepartment(department &);
};
