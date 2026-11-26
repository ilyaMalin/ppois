#include <UnitTest++/UnitTest++.h>
#include "security/permission.hpp"
#include <string>
#include "security/role.hpp"

TEST(permissionTest)
{
    permission value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validatePermission());
    permission invalid("", "");
    CHECK(!invalid.validatePermission());
    value.grantPermission();
    CHECK_EQUAL(std::string("grantpermission"), value.getStatus());
    role related("relatedId", "relatedName");
    value.linkRole(related);
}
