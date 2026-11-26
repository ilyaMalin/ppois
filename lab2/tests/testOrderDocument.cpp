#include <UnitTest++/UnitTest++.h>
#include "documents/orderDocument.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(orderDocumentTest)
{
    orderDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.issueOrder());
    orderDocument invalid("", "");
    CHECK(!invalid.issueOrder());
    value.cancelOrder();
    CHECK_EQUAL(std::string("cancelorder"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
