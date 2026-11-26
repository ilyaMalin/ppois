#include <UnitTest++/UnitTest++.h>
#include "organization/position.hpp"
#include <string>
#include "organization/department.hpp"

TEST(positionTest)
{
    position value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validatePosition());
    position invalid("", "");
    CHECK(!invalid.validatePosition());
    value.activatePosition();
    CHECK_EQUAL(std::string("activateposition"), value.getStatus());
    department related("relatedId", "relatedName");
    value.linkDepartment(related);
}
