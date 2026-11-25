#pragma once

#include <string>
#include "common/forward.hpp"

class auditLog
{
    std::string id;
    std::string name;
    std::string status;
    auditEvent *auditEventRef = nullptr;

public:
    auditLog(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateAuditLog() const;
    void closeAuditLog();
    void linkAuditEvent(auditEvent &);
};
