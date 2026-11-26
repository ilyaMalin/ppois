#pragma once

#include <string>
#include "common/forward.hpp"
class role;

class accessPolicy
{
    std::string id;
    std::string name;
    std::string status;
    role* roleRef = nullptr;

public:
    accessPolicy(std::string id = {}, std::string name = {});
    const std::string& getName() const;
    const std::string& getStatus() const;
    bool validatePolicy() const;
    void enablePolicy();
    void linkRole(role& value);
};
