#pragma once

#include <string>

class department
{
    std::string id;
    std::string name;
    std::string status;

public:
    department(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateDepartment() const;
    void openDepartment();
};
