#pragma once

#include <string>

class reportPeriod
{
    std::string id;
    std::string name;
    std::string status;

public:
    reportPeriod(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateReportPeriod() const;
    void closeReportPeriod();
};
