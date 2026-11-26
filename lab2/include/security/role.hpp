#pragma once

#include <string>

class role
{
    std::string id;
    std::string name;
    std::string status;

public:
    role(std::string id = {}, std::string name = {});
    const std::string& getName() const;
    const std::string& getStatus() const;
    bool validateRole() const;
    void activateRole();
};
