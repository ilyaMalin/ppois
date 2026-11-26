#include <UnitTest++/UnitTest++.h>
#include "workflow/approvalRule.hpp"
#include <string>
#include "security/role.hpp"

TEST(approvalRuleTest)
{
    approvalRule value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateApprovalRule());
    approvalRule invalid("", "");
    CHECK(!invalid.validateApprovalRule());
    value.enableApprovalRule();
    CHECK_EQUAL(std::string("enableapprovalrule"), value.getStatus());
    role related("relatedId", "relatedName");
    value.linkRole(related);
}
