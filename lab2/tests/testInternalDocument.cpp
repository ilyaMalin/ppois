#include <UnitTest++/UnitTest++.h>
#include "documents/internalDocument.hpp"
#include <string>
#include "organization/department.hpp"

TEST(internalDocumentTest)
{
    internalDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.publishInternal());
    internalDocument invalid("", "");
    CHECK(!invalid.publishInternal());
    value.withdrawInternal();
    CHECK_EQUAL(std::string("withdrawinternal"), value.getStatus());
    department related("relatedId", "relatedName");
    value.linkDepartment(related);
}
