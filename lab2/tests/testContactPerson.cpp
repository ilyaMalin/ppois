#include <UnitTest++/UnitTest++.h>
#include "organization/contactPerson.hpp"
#include <string>
#include "organization/counterparty.hpp"

TEST(contactPersonTest)
{
    contactPerson value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateContact());
    contactPerson invalid("", "");
    CHECK(!invalid.validateContact());
    value.confirmContact();
    CHECK_EQUAL(std::string("confirmcontact"), value.getStatus());
    counterparty related("relatedId", "relatedName");
    value.linkCounterparty(related);
}
