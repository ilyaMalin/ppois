#include <UnitTest++/UnitTest++.h>
#include "workflow/task.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(taskTest)
{
    task value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateTask());
    task invalid("", "");
    CHECK(!invalid.validateTask());
    value.completeTask();
    CHECK_EQUAL(std::string("complete"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
