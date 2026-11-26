#include <UnitTest++/UnitTest++.h>
#include "search/searchQuery.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(searchQueryTest)
{
    searchQuery value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateSearchQuery());
    searchQuery invalid("", "");
    CHECK(!invalid.validateSearchQuery());
    value.clearSearchQuery();
    CHECK_EQUAL(std::string("clearsearchquery"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
