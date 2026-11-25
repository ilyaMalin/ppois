#include "audit/auditEvent.hpp"

#include <utility>

auditEvent::auditEvent(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &auditEvent::getName() const
{
    return name;
}

const std::string &auditEvent::getStatus() const
{
    return status;
}

bool auditEvent::validateAuditEvent() const
{
    return !id.empty() && !name.empty();
}

void auditEvent::markEventReviewed()
{
    status = "markeventreviewed";
}

void auditEvent::linkUserAccount(userAccount &value)
{
    userAccountRef = &value;
}
