#include <UnitTest++/UnitTest++.h>
#include "organization/department.hpp"
#include <string>

TEST(departmentTest)
{
    department value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateDepartment());
    department invalid("", "");
    CHECK(!invalid.validateDepartment());
    value.openDepartment();
    CHECK_EQUAL(std::string("opendepartment"), value.getStatus());
}
