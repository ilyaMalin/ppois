#include <UnitTest++/UnitTest++.h>
#include "documents/documentCategory.hpp"
#include <string>
#include "documents/documentType.hpp"

TEST(documentCategoryTest)
{
    documentCategory value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.classifyDocument());
    documentCategory invalid("", "");
    CHECK(!invalid.classifyDocument());
    value.activateCategory();
    CHECK_EQUAL(std::string("activatecategory"), value.getStatus());
    documentType related("relatedId", "relatedName");
    value.linkDocumentType(related);
}
