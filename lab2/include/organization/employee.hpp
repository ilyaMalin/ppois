#pragma once

#include <string>
#include "common/forward.hpp"

class employee
{
    std::string id;
    std::string name;
    std::string status;
    department *departmentRef = nullptr;

public:
    employee(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateEmployee() const;
    void activateEmployee();
    void linkDepartment(department &);
};
