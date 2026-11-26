#include <UnitTest++/UnitTest++.h>
#include "registration/incomingChannel.hpp"
#include <string>

TEST(incomingChannelTest)
{
    incomingChannel value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateIncomingChannel());
    incomingChannel invalid("", "");
    CHECK(!invalid.validateIncomingChannel());
    value.enableIncomingChannel();
    CHECK_EQUAL(std::string("enableincomingchannel"), value.getStatus());
}
