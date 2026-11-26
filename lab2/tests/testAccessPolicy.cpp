#include <UnitTest++/UnitTest++.h>
#include "security/accessPolicy.hpp"
#include <string>
#include "security/role.hpp"

TEST(accessPolicyTest)
{
    accessPolicy value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validatePolicy());
    accessPolicy invalid("", "");
    CHECK(!invalid.validatePolicy());
    value.enablePolicy();
    CHECK_EQUAL(std::string("enablepolicy"), value.getStatus());
    role related("relatedId", "relatedName");
    value.linkRole(related);
}
