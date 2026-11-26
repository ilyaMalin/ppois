#include <UnitTest++/UnitTest++.h>
#include "documents/documentType.hpp"
#include <string>
#include "workflow/workflowDefinition.hpp"

TEST(documentTypeTest)
{
    documentType value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateType());
    documentType invalid("", "");
    CHECK(!invalid.validateType());
    value.enableType();
    CHECK_EQUAL(std::string("enabletype"), value.getStatus());
    workflowDefinition related("relatedId", "relatedName");
    value.linkWorkflowDefinition(related);
}
