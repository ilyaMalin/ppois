#include <UnitTest++/UnitTest++.h>
#include "audit/auditLog.hpp"
#include <string>
#include "audit/auditEvent.hpp"

TEST(auditLogTest)
{
    auditLog value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateAuditLog());
    auditLog invalid("", "");
    CHECK(!invalid.validateAuditLog());
    value.closeAuditLog();
    CHECK_EQUAL(std::string("closeauditlog"), value.getStatus());
    auditEvent related("relatedId", "relatedName");
    value.linkAuditEvent(related);
}
