#include "documents/reportDocument.hpp"

#include <utility>

reportDocument::reportDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &reportDocument::getName() const
{
    return name;
}

const std::string &reportDocument::getStatus() const
{
    return status;
}

bool reportDocument::finalizeReport() const
{
    return !id.empty() && !name.empty();
}

void reportDocument::publishReport()
{
    status = "publishreport";
}

void reportDocument::linkReportPeriod(reportPeriod &value)
{
    reportPeriodRef = &value;
}
