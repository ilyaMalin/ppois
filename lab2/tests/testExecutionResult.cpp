#include <UnitTest++/UnitTest++.h>
#include "workflow/executionResult.hpp"
#include <string>
#include "workflow/task.hpp"

TEST(executionResultTest)
{
    executionResult value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateExecutionResult());
    executionResult invalid("", "");
    CHECK(!invalid.validateExecutionResult());
    value.acceptExecutionResult();
    CHECK_EQUAL(std::string("acceptexecutionresult"), value.getStatus());
    task related("relatedId", "relatedName");
    value.linkTask(related);
}
