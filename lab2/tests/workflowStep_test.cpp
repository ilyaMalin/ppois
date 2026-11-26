#include <UnitTest++/UnitTest++.h>
#include "workflow/workflowStep.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(workflowStepTest)
{
    workflowStep value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateWorkflowStep());
    workflowStep invalid("", "");
    CHECK(!invalid.validateWorkflowStep());
    value.completeWorkflowStep();
    CHECK_EQUAL(std::string("completestep"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
