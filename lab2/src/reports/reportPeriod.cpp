#include "reports/reportPeriod.hpp"

#include <utility>

reportPeriod::reportPeriod(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &reportPeriod::getName() const
{
    return name;
}

const std::string &reportPeriod::getStatus() const
{
    return status;
}

bool reportPeriod::validateReportPeriod() const
{
    return !id.empty() && !name.empty();
}

void reportPeriod::closeReportPeriod()
{
    status = "closereportperiod";
}
