#pragma once

#include <string>
#include "common/forward.hpp"

class auditEvent
{
    std::string id;
    std::string name;
    std::string status;
    userAccount *userAccountRef = nullptr;

public:
    auditEvent(std::string id = {}, std::string name = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateAuditEvent() const;
    void markEventReviewed();
    void linkUserAccount(userAccount &value);
};
