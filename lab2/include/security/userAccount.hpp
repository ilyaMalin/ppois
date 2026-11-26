#pragma once

#include <string>
#include "common/forward.hpp"
class employee;

class userAccount
{
    std::string id;
    std::string name;
    std::string status;
    employee* employeeRef = nullptr;

public:
    userAccount(std::string id = {}, std::string name = {});
    const std::string& getName() const;
    const std::string& getStatus() const;
    bool validateAccount() const;
    void blockAccount();
    void linkEmployee(employee& value);
};
