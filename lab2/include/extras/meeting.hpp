#pragma once

#include <string>
#include "common/forward.hpp"

class meeting
{
    std::string id;
    std::string name;
    std::string status;
    department *departmentRef = nullptr;

public:
    meeting(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateMeeting() const;
    void closeMeeting();
    void linkDepartment(department &);
};
