#include <UnitTest++/UnitTest++.h>
#include "documents/memoDocument.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(memoDocumentTest)
{
    memoDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.submitMemo());
    memoDocument invalid("", "");
    CHECK(!invalid.submitMemo());
    value.withdrawMemo();
    CHECK_EQUAL(std::string("withdrawmemo"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
