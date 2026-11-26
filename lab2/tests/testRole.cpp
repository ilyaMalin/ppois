#include <UnitTest++/UnitTest++.h>
#include "security/role.hpp"
#include <string>

TEST(roleTest)
{
    role value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateRole());
    role invalid("", "");
    CHECK(!invalid.validateRole());
    value.activateRole();
    CHECK_EQUAL(std::string("activaterole"), value.getStatus());
}
