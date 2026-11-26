#pragma once

#include <string>
#include "common/forward.hpp"
class role;

class permission
{
    std::string id;
    std::string name;
    std::string status;
    role* roleRef = nullptr;

public:
    permission(std::string id = {}, std::string name = {});
    const std::string& getName() const;
    const std::string& getStatus() const;
    bool validatePermission() const;
    void grantPermission();
    void linkRole(role& value);
};
