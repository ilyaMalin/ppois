#include <UnitTest++/UnitTest++.h>
#include "audit/auditEvent.hpp"
#include <string>
#include "security/userAccount.hpp"

TEST(auditEventTest)
{
    auditEvent value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateAuditEvent());
    auditEvent invalid("", "");
    CHECK(!invalid.validateAuditEvent());
    value.markEventReviewed();
    CHECK_EQUAL(std::string("markeventreviewed"), value.getStatus());
    userAccount related("relatedId", "relatedName");
    value.linkUserAccount(related);
}
