#include <UnitTest++/UnitTest++.h>
#include "security/userAccount.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(userAccountTest)
{
    userAccount value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateAccount());
    userAccount invalid("", "");
    CHECK(!invalid.validateAccount());
    value.blockAccount();
    CHECK_EQUAL(std::string("blockaccount"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
