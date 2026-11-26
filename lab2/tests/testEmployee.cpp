#include <UnitTest++/UnitTest++.h>
#include "organization/employee.hpp"
#include <string>
#include "organization/department.hpp"

TEST(employeeTest)
{
    employee value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateEmployee());
    employee invalid("", "");
    CHECK(!invalid.validateEmployee());
    value.activateEmployee();
    CHECK_EQUAL(std::string("activateemployee"), value.getStatus());
    department related("relatedId", "relatedName");
    value.linkDepartment(related);
}
