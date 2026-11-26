#include <UnitTest++/UnitTest++.h>
#include "organization/counterparty.hpp"
#include <string>
#include "organization/address.hpp"

TEST(counterpartyTest)
{
    counterparty value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateCounterparty());
    counterparty invalid("", "");
    CHECK(!invalid.validateCounterparty());
    value.approveCounterparty();
    CHECK_EQUAL(std::string("approvecounterparty"), value.getStatus());
    address related("relatedId", "relatedName");
    value.linkAddress(related);
}
