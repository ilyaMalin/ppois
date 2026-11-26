#include <UnitTest++/UnitTest++.h>
#include "documents/document.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(documentTest)
{
    document value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.prepareDocument());
    document invalid("", "");
    CHECK(!invalid.prepareDocument());
    value.submitDocument();
    CHECK_EQUAL(std::string("submit"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
