#include <UnitTest++/UnitTest++.h>
#include "registration/registrationJournal.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(registrationJournalTest)
{
    registrationJournal value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateJournal());
    registrationJournal invalid("", "");
    CHECK(!invalid.validateJournal());
    value.closeJournal();
    CHECK_EQUAL(std::string("closejournal"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
