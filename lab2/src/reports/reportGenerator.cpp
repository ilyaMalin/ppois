#include "reports/reportGenerator.hpp"

#include <utility>

reportGenerator::reportGenerator(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &reportGenerator::getName() const
{
    return name;
}

const std::string &reportGenerator::getStatus() const
{
    return status;
}

bool reportGenerator::validateReportRequest() const
{
    return !id.empty() && !name.empty();
}

void reportGenerator::generateReport()
{
    status = "generatereport";
}

void reportGenerator::linkDepartment(department &value)
{
    departmentRef = &value;
}
