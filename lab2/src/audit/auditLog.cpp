#include "audit/auditLog.hpp"

#include <utility>

auditLog::auditLog(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &auditLog::getName() const
{
    return name;
}

const std::string &auditLog::getStatus() const
{
    return status;
}

bool auditLog::validateAuditLog() const
{
    return !id.empty() && !name.empty();
}

void auditLog::closeAuditLog()
{
    status = "closeauditlog";
}

void auditLog::linkAuditEvent(auditEvent &value)
{
    auditEventRef = &value;
}
