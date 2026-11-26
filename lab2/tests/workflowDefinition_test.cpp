#include <UnitTest++/UnitTest++.h>
#include "workflow/workflowDefinition.hpp"
#include <string>
#include "documents/documentType.hpp"

TEST(workflowDefinitionTest)
{
    workflowDefinition value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateWorkflowDefinition());
    workflowDefinition invalid("", "");
    CHECK(!invalid.validateWorkflowDefinition());
    value.publishWorkflow();
    CHECK_EQUAL(std::string("publish"), value.getStatus());
    documentType related("relatedId", "relatedName");
    value.linkDocumentType(related);
}
