#include <UnitTest++/UnitTest++.h>
#include "documents/templateField.hpp"
#include <string>
#include "documents/documentTemplate.hpp"

TEST(templateFieldTest)
{
    templateField value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateTemplateField());
    templateField invalid("", "");
    CHECK(!invalid.validateTemplateField());
    value.requireTemplateField();
    CHECK_EQUAL(std::string("requiretemplatefield"), value.getStatus());
    documentTemplate related("relatedId", "relatedName");
    value.linkDocumentTemplate(related);
}
