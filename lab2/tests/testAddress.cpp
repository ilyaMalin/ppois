#include <UnitTest++/UnitTest++.h>
#include "organization/address.hpp"
#include <string>

TEST(addressTest)
{
    address value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateAddress());
    address invalid("", "");
    CHECK(!invalid.validateAddress());
    value.markAddressVerified();
    CHECK_EQUAL(std::string("markaddressverified"), value.getStatus());
}
