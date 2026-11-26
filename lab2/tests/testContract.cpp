#include <UnitTest++/UnitTest++.h>
#include "documents/contract.hpp"
#include <string>
#include "organization/counterparty.hpp"

TEST(contractTest)
{
    contract value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateContract());
    contract invalid("", "");
    CHECK(!invalid.validateContract());
    value.signContract();
    CHECK_EQUAL(std::string("signcontract"), value.getStatus());
    counterparty related("relatedId", "relatedName");
    value.linkCounterparty(related);
}
