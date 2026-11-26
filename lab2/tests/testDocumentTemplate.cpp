#include <UnitTest++/UnitTest++.h>
#include "documents/documentTemplate.hpp"
#include <string>
#include "documents/documentType.hpp"

TEST(documentTemplateTest)
{
    documentTemplate value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateTemplate());
    documentTemplate invalid("", "");
    CHECK(!invalid.validateTemplate());
    value.publishTemplate();
    CHECK_EQUAL(std::string("publishtemplate"), value.getStatus());
    documentType related("relatedId", "relatedName");
    value.linkDocumentType(related);
}
