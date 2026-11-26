#pragma once

#include <string>
#include "common/forward.hpp"

class reportGenerator
{
    std::string id;
    std::string name;
    std::string status;
    department *departmentRef = nullptr;

public:
    reportGenerator(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateReportRequest() const;
    void generateReport();
    void linkDepartment(department &);
};
