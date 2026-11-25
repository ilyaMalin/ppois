#pragma once

#include <string>
#include "common/forward.hpp"

class reportDocument
{
    std::string id;
    std::string name;
    std::string status;
    reportPeriod *reportPeriodRef = nullptr;

public:
    reportDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool finalizeReport() const;
    void publishReport();
    void linkReportPeriod(reportPeriod &);
};
