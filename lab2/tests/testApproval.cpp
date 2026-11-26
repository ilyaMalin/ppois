#include <UnitTest++/UnitTest++.h>
#include "workflow/approval.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(approvalTest)
{
    approval value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateApproval());
    approval invalid("", "");
    CHECK(!invalid.validateApproval());
    value.approveDocument();
    CHECK_EQUAL(std::string("approve"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
