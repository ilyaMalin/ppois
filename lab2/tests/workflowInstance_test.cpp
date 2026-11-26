#include <UnitTest++/UnitTest++.h>
#include "workflow/workflowInstance.hpp"
#include <string>
#include "documents/document.hpp"

TEST(workflowInstanceTest)
{
    workflowInstance value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateWorkflowInstance());
    workflowInstance invalid("", "");
    CHECK(!invalid.validateWorkflowInstance());
    value.startWorkflow();
    CHECK_EQUAL(std::string("start"), value.getStatus());
    document related("relatedId", "relatedName");
    value.linkDocument(related);
}
